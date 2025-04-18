/*
 * Ethernet driver for the Atmel AT91RM9200 (Thunder)
 *
 * (c) SAN People (Pty) Ltd
 *
 * Based on an earlier Atmel EMAC macrocell driver by Atmel and Lineo Inc.
 * Initial version by Rick Bronson 01/11/2003
 *
 * Intel LXT971A PHY support by Christopher Bahns & David Knickerbocker
 *   (Polaroid Corporation)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#undef CONFIG_AT91_ETHER_RMII /**/
#define END_CACHE_VIRT_TO_PHYS(x) x

#define ether_crc(length, data)    bitreverse(crc32_le(~0, data, length))
unsigned long bitreverse(unsigned long x)
{
	x = (x >> 16) | (x << 16);
	x = (x >> 8 & 0x00ff00ff) | (x << 8 & 0xff00ff00);
	x = (x >> 4 & 0x0f0f0f0f) | (x << 4 & 0xf0f0f0f0);
	x = (x >> 2 & 0x33333333) | (x << 2 & 0xcccccccc);
	x = (x >> 1 & 0x55555555) | (x << 1 & 0xaaaaaaaa);
	return x;
}

#include "crc32table.h"
unsigned long  crc32_le(unsigned long crc, unsigned char const *p, int len)
{
	const unsigned long      *b =(unsigned long *)p;
	const unsigned long      *tab = crc32table_le;


#define DO_CRC(x) crc = tab[ (crc ^ (x)) & 255 ] ^ (crc>>8)



	/* Align it */
	if(!(((long)b)&3 && len)){
		do {
			DO_CRC(*((unsigned char *)b)++);
		} while ((--len) && ((long)b)&3 );
	}
	if((len >= 4)){
		/* load data 32 bits wide, xor data 32 bits wide. */
		size_t save_len = len & 3;
	        len = len >> 2;
		--b; /* use pre increment below(*++b) for speed */
		do {
			crc ^= *++b;
			DO_CRC(0);
			DO_CRC(0);
			DO_CRC(0);
			DO_CRC(0);
		} while (--len);
		b++; /* point to next byte(s) */
		len = save_len;
	}
	/* And the last few bytes */
	if(len){
		do {
			DO_CRC(*((unsigned char *)b)++);
		} while (--len);
	}

	return (crc);
#undef ENDIAN_SHIFT
#undef DO_CRC


}
#define barrier() 

static __inline int is_valid_ether_addr( unsigned char *addr )
{
	const char zaddr[6] = {0,};

	return !(addr[0]&1) && memcmp( addr, zaddr, 6);
}
static	struct at91_private  at91_mac_private;


/* ........................... PHY INTERFACE ........................... */

/*
 * Enable the MDIO bit in MAC control register
 * When not called from an interrupt-handler, access to the PHY must be
 *  protected by a spinlock.
 */
static void enable_mdi(AT91PS_EMAC regs)
{
	regs->EMAC_CTL |= AT91C_EMAC_MPE;	/* enable management port */
}

/*
 * Disable the MDIO bit in the MAC control register
 */
static void disable_mdi(AT91PS_EMAC regs)
{
	regs->EMAC_CTL &= ~AT91C_EMAC_MPE;	/* disable management port */
}

/*
 * Write value to the a PHY register
 * Note: MDI interface is assumed to already have been enabled.
 */
static void write_phy(AT91PS_EMAC regs, unsigned char phy_addr, unsigned char address, unsigned int value)
{
	regs->EMAC_MAN = (AT91C_EMAC_HIGH | AT91C_EMAC_CODE_802_3 | AT91C_EMAC_RW_W
		| ((phy_addr & 0x1f) << 23) | (address << 18)) + (value & 0xffff);

	/* Wait until IDLE bit in Network Status register is cleared */
	/* TODO: Enforce some maximum loop-count?*/
	while (!(regs->EMAC_SR & AT91C_EMAC_IDLE)) { barrier(); }
}

/*
 * Read value stored in a PHY register.
 * Note: MDI interface is assumed to already have been enabled.
 */
static void read_phy(AT91PS_EMAC regs, unsigned char phy_addr, unsigned char address, unsigned int *value)
{
	regs->EMAC_MAN = AT91C_EMAC_HIGH | AT91C_EMAC_CODE_802_3 | AT91C_EMAC_RW_R
		| ((phy_addr & 0x1f) << 23) | (address << 18);

	/* Wait until IDLE bit in Network Status register is cleared */
	/* TODO: Enforce some maximum loop-count?*/
	while (!(regs->EMAC_SR & AT91C_EMAC_IDLE)) { barrier(); }

	*value = (regs->EMAC_MAN & 0x0000ffff);
}

/* ........................... PHY MANAGEMENT .......................... */

/*
 * Access the PHY to determine the current Link speed and Mode, and update the
 * MAC accordingly.
 * If no link or auto-negotiation is busy, then no changes are made.
 * Returns:  0 : OK
 *          -1 : No link
 *          -2 : AutoNegotiation still in progress
 */
static int update_linkspeed(struct net_device *dev, AT91PS_EMAC regs) {
	unsigned int  mac_cfg;
	

	
	mac_cfg = regs->EMAC_CFG & ~(AT91C_EMAC_SPD | AT91C_EMAC_FD);
	

    regs->EMAC_CFG = mac_cfg | AT91C_EMAC_SPD | AT91C_EMAC_FD;

	return 0;
}

/*
 * Handle interrupts from the PHY
 */
static void at91ether_phy_interrupt(void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct at91_private *lp = (struct at91_private *) dev->priv;
	AT91PS_EMAC emac = (AT91PS_EMAC) dev->base_addr;
	int status;
	unsigned int phy;

	enable_mdi(emac);
	if (lp->phy_type == MII_DM9161_ID)
		read_phy(emac, 0, MII_DSINTR_REG, &phy);	/* ack interrupt in Davicom PHY */
	else if (lp->phy_type == MII_LXT971A_ID)
		read_phy(emac, 0, MII_ISINTS_REG, &phy);	/* ack interrupt in Intel PHY */
		
	status = AT91_SYS->PIOC_ISR;		/* acknowledge interrupt in PIO */

	status = update_linkspeed(dev, emac);
#if 0
	if (status == -1) {			/* link is down */
		netif_carrier_off(dev);

	} else if (status == -2) {		/* auto-negotiation in progress */
		/* Do nothing - another interrupt generated when negotiation complete */
	} else {				/* link is operational */
		netif_carrier_on(dev);
	}
#endif
	disable_mdi(emac);
}

/*
 * Initialize and enable the PHY interrupt when link-state changes
 */
static void enable_phyirq(struct net_device *dev, AT91PS_EMAC regs)
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	unsigned int dsintr, status;

	if (lp->phy_type == MII_RTL8201BL_ID) return;

	/* TODO: Check error code.  Really need a generic PIO (interrupt)*/
	


	spin_lock_irq(&lp->lock);
	enable_mdi(regs);
		
	if (lp->phy_type == MII_DM9161_ID) {		/* for Davicom PHY */
		read_phy(regs, 0, MII_DSINTR_REG, &dsintr);
		dsintr = dsintr & ~0xf00;		/* clear bits 8..11 */
		write_phy(regs, 0, MII_DSINTR_REG, dsintr);
	}
	else if (lp->phy_type == MII_LXT971A_ID) {	/* for Intel PHY */
		read_phy(regs, 0, MII_ISINTE_REG, &dsintr);
		dsintr = dsintr | 0xf2;			/* set bits 1, 4..7 */
		write_phy(regs, 0, MII_ISINTE_REG, dsintr);
	}
		
	disable_mdi(regs);
	spin_unlock_irq(&lp->lock);
}

/*
 * Disable the PHY interrupt
 */
static void disable_phyirq(struct net_device *dev, AT91PS_EMAC regs)
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	unsigned int dsintr;
	if (lp->phy_type == MII_RTL8201BL_ID) return;
	spin_lock_irq(&lp->lock);
	enable_mdi(regs);

	if (lp->phy_type == MII_DM9161_ID) {		/* for Davicom PHY */
		read_phy(regs, 0, MII_DSINTR_REG, &dsintr);
		dsintr = dsintr | 0xf00;			/* set bits 8..11 */
		write_phy(regs, 0, MII_DSINTR_REG, dsintr);
	}
	else if (lp->phy_type == MII_LXT971A_ID) {	/* for Intel PHY */
		read_phy(regs, 0, MII_ISINTE_REG, &dsintr);
		dsintr = dsintr & ~0xf2;			/* clear bits 1, 4..7 */
		write_phy(regs, 0, MII_ISINTE_REG, dsintr);
	}

	disable_mdi(regs);
	spin_unlock_irq(&lp->lock);

#ifdef CONFIG_MACH_CSB337
	AT91_SYS->PIOC_IDR = AT91C_PIO_PC2;		/* Disable interrupt */
#else
	AT91_SYS->PIOC_IDR = AT91C_PIO_PC4;		/* Disable interrupt */
#endif
	free_irq(AT91C_ID_PIOC, dev);			/* Free interrupt handler */
}

/*
 * Perform a software reset of the PHY.
 */
#if 1
static void reset_phy(struct net_device *dev, AT91PS_EMAC regs)
{

	int lockKey;
	unsigned int bmcr;

	    lockKey = intLock();
	enable_mdi(regs);

	/* Perform PHY reset */
	write_phy(regs, 0, MII_BMCR, BMCR_RESET);

	/* Wait until PHY reset is complete */
	do {
		read_phy(regs, 0, MII_BMCR, &bmcr);
	} while (!(bmcr && BMCR_RESET));

	disable_mdi(regs);
	intUnlock(lockKey);
}
#endif

/* ......................... ADDRESS MANAGEMENT ........................ */

/*
 * Set the ethernet MAC address in dev->dev_addr
 */
static void get_mac_address(struct net_device *dev) {
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	char addr[6];
	unsigned int hi, lo;

	/* Check if bootloader set address in Specific-Address 1 */
	hi = regs->EMAC_SA1H;
	lo = regs->EMAC_SA1L;
#ifdef CONFIG_MACH_CSB337
	addr[5] = (lo & 0xff);			/* The CSB337 bootloader stores the MAC the wrong-way around */
	addr[4] = (lo & 0xff00) >> 8;
	addr[3] = (lo & 0xff0000) >> 16;
	addr[2] = (lo & 0xff000000) >> 24;
	addr[1] = (hi & 0xff);
	addr[0] = (hi & 0xff00) >> 8;
#else
	addr[0] = (lo & 0xff);
	addr[1] = (lo & 0xff00) >> 8;
	addr[2] = (lo & 0xff0000) >> 16;
	addr[3] = (lo & 0xff000000) >> 24;
	addr[4] = (hi & 0xff);
	addr[5] = (hi & 0xff00) >> 8;
#endif

	if (is_valid_ether_addr(addr)) {
		memcpy(dev->dev_addr, &addr, 6);
		return;
	}

	/* Check if bootloader set address in Specific-Address 2 */
	hi = regs->EMAC_SA2H;
	lo = regs->EMAC_SA2L;
#ifdef CONFIG_MACH_CSB337
	addr[5] = (lo & 0xff);			/* The CSB337 bootloader stores the MAC the wrong-way around */
	addr[4] = (lo & 0xff00) >> 8;
	addr[3] = (lo & 0xff0000) >> 16;
	addr[2] = (lo & 0xff000000) >> 24;
	addr[1] = (hi & 0xff);
	addr[0] = (hi & 0xff00) >> 8;
#else
	addr[0] = (lo & 0xff);
	addr[1] = (lo & 0xff00) >> 8;
	addr[2] = (lo & 0xff0000) >> 16;
	addr[3] = (lo & 0xff000000) >> 24;
	addr[4] = (hi & 0xff);
	addr[5] = (hi & 0xff00) >> 8;
#endif

	if (is_valid_ether_addr(addr)) {
		memcpy(dev->dev_addr, &addr, 6);
		return;
	}
}

/*
 * Program the hardware MAC address from dev->dev_addr.
 */
static int update_mac_address(struct net_device *dev)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

	regs->EMAC_SA1L = (dev->dev_addr[3] << 24) | (dev->dev_addr[2] << 16) | (dev->dev_addr[1] << 8) | (dev->dev_addr[0]);
	regs->EMAC_SA1H = (dev->dev_addr[5] << 8) | (dev->dev_addr[4]);

	regs->EMAC_SA2L = 0;
	regs->EMAC_SA2H = 0;
	return 0;
}

/*
 * Store the new hardware address in dev->dev_addr, and update the MAC.
 */
#if 0
static int set_mac_address(struct net_device *dev, void* addr)
{
	struct sockaddr *address = addr;

	if (!is_valid_ether_addr(address->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, address->sa_data, ETH_ALEN);
	update_mac_address(dev);

	printk("%s: Setting MAC address to %02x:%02x:%02x:%02x:%02x:%02x\n", dev->name,
		dev->dev_addr[0], dev->dev_addr[1], dev->dev_addr[2],
		dev->dev_addr[3], dev->dev_addr[4], dev->dev_addr[5]);

	return 0;
}
#endif

/*
 * Add multicast addresses to the internal multicast-hash table.
 */
static void at91ether_sethashtable(struct net_device *dev, AT91PS_EMAC regs)
{

	struct dev_mc_list *curr;
	unsigned char mc_filter[2];
	unsigned int i, bitnr;

	mc_filter[0] = mc_filter[1] = 0;

	curr = dev->mc_list;
	for (i = 0; i < dev->mc_count; i++, curr = curr->next) {
		if (!curr) break;	/* unexpected end of list */

		bitnr = ether_crc(ETH_ALEN, curr->dmi_addr) >> 26;
		mc_filter[bitnr >> 5] |= 1 << (bitnr & 31);
	}

	regs->EMAC_HSH = mc_filter[1];
	regs->EMAC_HSL = mc_filter[0];
}

/*
 * Enable/Disable promiscuous and multicast modes.
 */
static void at91ether_set_rx_mode(struct net_device *dev)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

	if (dev->flags & IFF_PROMISC) {			/* Enable promiscuous mode */
		regs->EMAC_CFG |= AT91C_EMAC_CAF;
	} else if (dev->flags & (~IFF_PROMISC)) {	/* Disable promiscuous mode */
		regs->EMAC_CFG &= ~AT91C_EMAC_CAF;
	}

	if (dev->flags & IFF_ALLMULTI) {		/* Enable all multicast mode */
		regs->EMAC_HSH = -1;
		regs->EMAC_HSL = -1;
		regs->EMAC_CFG |= AT91C_EMAC_MTI;
	} else if (dev->mc_count > 0) {			/* Enable specific multicasts */
		at91ether_sethashtable(dev, regs);
		regs->EMAC_CFG |= AT91C_EMAC_MTI;
	} else if (dev->flags & (~IFF_ALLMULTI)) {	/* Disable all multicast mode */
		regs->EMAC_HSH = 0;
		regs->EMAC_HSL = 0;
		regs->EMAC_CFG &= ~AT91C_EMAC_MTI;
	}
}

/* ............................... IOCTL ............................... */
#if 0
static int mdio_read(struct net_device *dev, int phy_id, int location)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	unsigned int value;

	read_phy(regs, phy_id, location, &value);
	return value;
}

static void mdio_write(struct net_device *dev, int phy_id, int location, int value)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

	write_phy(regs, phy_id, location, value);
}
#endif
#if 0
/*
 * ethtool support.
 */
static int at91ether_ethtool_ioctl (struct net_device *dev, void *useraddr)
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	unsigned long ethcmd;
	int res = 0;

	if (copy_from_user (&ethcmd, useraddr, sizeof (ethcmd)))
		return -EFAULT;

	spin_lock_irq(&lp->lock);
	enable_mdi(regs);

	switch (ethcmd) {
	case ETHTOOL_GSET: {
		struct ethtool_cmd ecmd = { ETHTOOL_GSET };
		res = mii_ethtool_gset(&lp->mii, &ecmd);
		if (lp->phy_media == PORT_FIBRE) {		/* override media type since mii.c doesn't know */
			ecmd.supported = SUPPORTED_FIBRE;
			ecmd.port = PORT_FIBRE;
		}
		if (copy_to_user(useraddr, &ecmd, sizeof(ecmd)))
			res = -EFAULT;
		break;
	}
	case ETHTOOL_SSET: {
		struct ethtool_cmd ecmd;
		if (copy_from_user(&ecmd, useraddr, sizeof(ecmd)))
			res = -EFAULT;
		else
			res = mii_ethtool_sset(&lp->mii, &ecmd);
		break;
	}
	case ETHTOOL_NWAY_RST: {
		res = mii_nway_restart(&lp->mii);
		break;
	}
	case ETHTOOL_GLINK: {
		struct ethtool_value edata = { ETHTOOL_GLINK };
		edata.data = mii_link_ok(&lp->mii);
		if (copy_to_user(useraddr, &edata, sizeof(edata)))
			res = -EFAULT;
		break;
	}
	default:
		res = -EOPNOTSUPP;
	}

	disable_mdi(regs);
	spin_unlock_irq(&lp->lock);

	return res;
}

/*
 * User-space ioctl interface.
 */
static int at91ether_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	switch(cmd) {
	case SIOCETHTOOL:
		return at91ether_ethtool_ioctl(dev, (void *) rq->ifr_data);
	default:
		return -EOPNOTSUPP;
	}
}
#endif
/* ................................ MAC ................................ */

/*
 * Initialize and start the Receiver and Transmit subsystems
 */
 
 
static void at91ether_start(struct net_device *dev)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	struct at91_private *lp = (struct at91_private *) dev->priv;
	int i;
	struct recv_desc_bufs *dlist, *dlist_phys;
	dlist = lp->dlist;
	dlist_phys = lp->dlist_phys;

	for (i = 0; i < MAX_RX_DESCR; i++) {

		dlist->descriptors[i].addr = (unsigned int)dlist->recv_buf[i];

		dlist->descriptors[i].size = 0;
	}

	/* Set the Wrap bit on the last descriptor */
	dlist->descriptors[i-1].addr |= EMAC_DESC_WRAP;

	/* Reset buffer index */
	lp->rxBuffIndex = 0;

	/* Program address of descriptor list in Rx Buffer Queue register */
	regs->EMAC_RBQP = (AT91_REG) dlist_phys;

	/* Enable Receive and Transmit */
	regs->EMAC_CTL |= (AT91C_EMAC_RE | AT91C_EMAC_TE);
	intEnable(AT91C_ID_PIOC);
	intEnable(dev->irq);
}

/*
 * Open the ethernet interface
 */
static int at91ether_open(struct net_device *dev)
{
   	 int lockKey;
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

        if (!is_valid_ether_addr(dev->dev_addr))
        	return -EADDRNOTAVAIL;

	AT91_SYS->PMC_PCER = 1 << AT91C_ID_EMAC;	/* Re-enable Peripheral clock */
	regs->EMAC_CTL |= AT91C_EMAC_CSR;		/* Clear internal statistics */

	/* Update the MAC address (incase user has changed it) */
	update_mac_address(dev);

	/* Enable PHY interrupt */
	/*enable_phyirq(dev, regs);*/

	/* Enable MAC interrupts */
	regs->EMAC_IER = AT91C_EMAC_RCOM | AT91C_EMAC_RBNA
			| AT91C_EMAC_TUND | AT91C_EMAC_RTRY | AT91C_EMAC_TCOM
			| AT91C_EMAC_ROVR | AT91C_EMAC_HRESP;

	/* Determine current link speed */
    lockKey = intLock();

	enable_mdi(regs);
	(void) update_linkspeed(dev, regs);
	disable_mdi(regs);
    intUnlock(lockKey);

	at91ether_start(dev);
/*	netif_start_queue(dev);*/
	return 0;
}

/*
 * Close the interface
 */
static int at91ether_close(struct net_device *dev)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;

	/* Disable Receiver and Transmitter */
	regs->EMAC_CTL &= ~(AT91C_EMAC_TE | AT91C_EMAC_RE);

	/* Disable PHY interrupt */
	/*disable_phyirq(dev, regs);*/

	/* Disable MAC interrupts */
	regs->EMAC_IDR = AT91C_EMAC_RCOM | AT91C_EMAC_RBNA
			| AT91C_EMAC_TUND | AT91C_EMAC_RTRY | AT91C_EMAC_TCOM
			| AT91C_EMAC_ROVR | AT91C_EMAC_HRESP;

	/*netif_stop_queue(dev);*/

	AT91_SYS->PMC_PCDR = 1 << AT91C_ID_EMAC;	/* Disable Peripheral clock */

	return 0;
}
/*
 * Update the current statistics from the internal statistics registers.
 */
#if 0
static struct net_device_stats *at91ether_stats(struct net_device *dev)
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	AT91PS_EMAC regs = (AT91PS_EMAC) dev->base_addr;
	int ale, lenerr, seqe, lcol, ecol;

	/*if (netif_running(dev)) */{
		lp->stats.rx_packets += regs->EMAC_OK;			/* Good frames received */
		ale = regs->EMAC_ALE;
		lp->stats.rx_frame_errors += ale;			/* Alignment errors */
		lenerr = regs->EMAC_ELR + regs->EMAC_USF;
		lp->stats.rx_length_errors += lenerr;			/* Excessive Length or Undersize Frame error */
		seqe = regs->EMAC_SEQE;
		lp->stats.rx_crc_errors += seqe;			/* CRC error */
		lp->stats.rx_fifo_errors += regs->EMAC_DRFC;		/* Receive buffer not available */
		lp->stats.rx_errors += (ale + lenerr + seqe + regs->EMAC_CDE + regs->EMAC_RJB);

		lp->stats.tx_packets += regs->EMAC_FRA;			/* Frames successfully transmitted */
		lp->stats.tx_fifo_errors += regs->EMAC_TUE;		/* Transmit FIFO underruns */
		lp->stats.tx_carrier_errors += regs->EMAC_CSE;		/* Carrier Sense errors */
		lp->stats.tx_heartbeat_errors += regs->EMAC_SQEE;	/* Heartbeat error */

		lcol = regs->EMAC_LCOL;
		ecol = regs->EMAC_ECOL;
		lp->stats.tx_window_errors += lcol;			/* Late collisions */
		lp->stats.tx_aborted_errors += ecol;			/* 16 collisions */

		lp->stats.collisions += (regs->EMAC_SCOL + regs->EMAC_MCOL + lcol + ecol);
	}
	return &lp->stats;
}
#endif
/*
 * Extract received frame from buffer descriptors and sent to upper layers.
 * (Called from interrupt context)
 */
static void at91ether_rx(struct net_device *dev)
{
/*	unsigned char *p_recv;*/
/*	struct sk_buff *skb;*/
/*	unsigned int pktlen;*/
	AT91PS_EMAC emac = (AT91PS_EMAC) dev->base_addr;
	if (emac->EMAC_RSR & AT91C_EMAC_REC)
		emac->EMAC_RSR |= AT91C_EMAC_REC;
	if(( !dev->bPolling) && (!dev->bRxHandler))
        {
            dev->bRxHandler = TRUE;

            netJobAdd((FUNCPTR)at91EthRxHandler, (int)dev, 0, 0, 0, 0);
        } 

}

/*
 * MAC interrupt handler
 */
static void at91ether_interrupt(ETH_DRV_CTRL *dev )
{
	struct at91_private *lp = (struct at91_private *) dev->priv;
	AT91PS_EMAC emac = (AT91PS_EMAC) dev->base_addr;
	unsigned long intstatus;

	/* MAC Interrupt Status register indicates what interrupts are pending.
	   It is automatically cleared once read. */
	intstatus = emac->EMAC_ISR;

	if (intstatus & AT91C_EMAC_RCOM)		/* Receive complete */
		at91ether_rx(dev);

	if (intstatus & AT91C_EMAC_TCOM) {		/* Transmit complete */
	
		/* The TCOM bit is set even if the transmission failed. */
		if (intstatus & (AT91C_EMAC_TUND | AT91C_EMAC_RTRY))
			lp->stats.tx_errors += 1;

	        if ((!dev->bPolling) && (!dev->bTxHandler))
	        {
	            dev->bTxHandler = TRUE;
	
	            netJobAdd((FUNCPTR)at91EthTxHandler, (int)dev, 0, 0, 0, 0);
	        }
		/*dev_kfree_skb_irq(lp->skb);*/
		/*pci_unmap_single(NULL, lp->skb_physaddr, lp->skb_length, PCI_DMA_TODEVICE);*/
		/*netif_wake_queue(dev);*/
	}

	/* Work-around for Errata #11 */
	if (intstatus & AT91C_EMAC_RBNA) {
		emac->EMAC_CTL &= ~AT91C_EMAC_RE;
		emac->EMAC_CTL |= AT91C_EMAC_RE;
	}
	
	if (intstatus & AT91C_EMAC_ROVR)
		printk("%s: ROVR error\n", dev->name);
}

/*
 * Initialize the ethernet interface
 */


static int at91ether_setup(struct net_device *dev, unsigned long phy_type)
{

	AT91PS_EMAC regs;
	static int already_initialized = 0;
	struct at91_private *lp = &at91_mac_private;
	unsigned int val;
	unsigned long addr;
	if (already_initialized)
		return 0;

/*	dev = init_etherdev(dev, sizeof(struct at91_private));*/
	dev->base_addr = AT91C_VA_BASE_EMAC;
	dev->irq = AT91C_ID_EMAC;


	/* Install the interrupt handler */
	if (request_irq(dev->irq, at91ether_interrupt, 0, dev->name, dev))
		return -EBUSY;


	memset(lp, 0, sizeof(struct at91_private));
	dev->priv = lp;

	/* Allocate memory for DMA Receive descriptors */
	addr = (unsigned long) cacheDmaMalloc(sizeof(struct recv_desc_bufs)+0x100);
	if(addr&0xFF) addr=(addr&0xffffff00)+0x100;
	lp->dlist = (struct recv_desc_bufs *) addr;
	lp->dlist_phys  = lp->dlist ; /* cacheDrvVirtToPhys();*/


	spin_lock_init(&lp->lock);
/*
	ether_setup(dev);
	dev->open = at91ether_open;
	dev->stop = at91ether_close;
	dev->hard_start_xmit = at91ether_tx;
	dev->get_stats = at91ether_stats;
	dev->set_multicast_list = at91ether_set_rx_mode;
	dev->do_ioctl = at91ether_ioctl;
	dev->set_mac_address = set_mac_address;
*/
	get_mac_address(dev);		/* Get ethernet address and store it in dev->dev_addr */
	update_mac_address(dev);	/* Program ethernet address into MAC */

	regs = (AT91PS_EMAC) dev->base_addr;
	regs->EMAC_CTL = 0;

#ifdef CONFIG_AT91_ETHER_RMII
	regs->EMAC_CFG = AT91C_EMAC_BIG | AT91C_EMAC_RMII;
#else
	regs->EMAC_CFG = AT91C_EMAC_BIG;
#endif
	if (phy_type == MII_LXT971A_ID)
		regs->EMAC_CFG |= AT91C_EMAC_CLK_HCLK_64;	/* MDIO clock = system clock/64 */

	if (phy_type == MII_DM9161_ID) {
		spin_lock_irq(&lp->lock);
		enable_mdi(regs);

		read_phy(regs, 0, MII_DSCR_REG, &val);
		if ((val & (1 << 10)) == 0)			/* DSCR bit 10 is 0 -- fiber mode */
			lp->phy_media = PORT_FIBRE;

		disable_mdi(regs);
		spin_unlock_irq(&lp->lock);
	}
	if (phy_type == MII_RTL8201BL_ID) 
		regs->EMAC_CFG |= AT91C_EMAC_CLK_HCLK_64;	/* MDIO clock = system clock/64 */
	

/*	lp->mii.dev = dev;		
	lp->mii.mdio_read = mdio_read;
	lp->mii.mdio_write = mdio_write;
	*/
	lp->phy_type = phy_type;	/* Type of PHY connected */

	/* Determine current link speed */
	spin_lock_irq(&lp->lock);
	enable_mdi(regs);
	(void) update_linkspeed(dev, regs);
	disable_mdi(regs);
	spin_unlock_irq(&lp->lock);


	if (phy_type == MII_DM9161_ID)
		printk(KERN_INFO "%s: Davicom 9196 PHY %s\n", dev->name, (lp->phy_media == PORT_FIBRE) ? "(Fiber)" : "(Copper)");
	else if (phy_type == MII_LXT971A_ID)
		printk(KERN_INFO "%s: Intel LXT971A PHY\n", dev->name);
	if (phy_type == MII_RTL8201BL_ID)
		printk(KERN_INFO "%s: Realtek 8201BL PHY\n", dev->name);
	already_initialized = 1;
	return 0;
}

/*
 * Detect MAC and PHY and perform initialization
 */
static int at91ether_probe(struct net_device *dev)
{
	AT91PS_EMAC regs = (AT91PS_EMAC) AT91C_VA_BASE_EMAC;
	unsigned int phyid1, phyid2,phyid3;
	int detected = -1;

	/* Configure the hardware - RMII vs MII mode */
#ifdef CONFIG_AT91_ETHER_RMII
	AT91_CfgPIO_EMAC_RMII();
#else
	AT91_CfgPIO_EMAC_MII();
#endif

	AT91_CfgPIO_EMAC_PHY();				/* Configure PHY interrupt */
	AT91_SYS->PMC_PCER = 1 << AT91C_ID_EMAC;	/* Enable Peripheral clock */

	/* Read the PHY ID registers */

	/*
	enable_mdi(regs);

	printf (" \n  ");
	for(phyid3=0;phyid3<32;phyid3++)
	{

	
	printf (" \n %08x \n ",phyid3);
	for (phyid2=0;phyid2<32;phyid2++)
		{
		read_phy(regs, phyid3, phyid2, &phyid1);
		printf (" IIIDDD %08x, %08x\n ", phyid2, phyid1 );
		}
	}

	disable_mdi(regs);
	*/
	/* Davicom 9161: PHY_ID1 = 0x181  PHY_ID2 = B881 */

	
		detected = at91ether_setup(dev, MII_LXT971A_ID);


	AT91_SYS->PMC_PCDR = 1 << AT91C_ID_EMAC;	/* Disable Peripheral clock */

	return detected;
}









