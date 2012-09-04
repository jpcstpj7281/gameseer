/*
 * Ethernet driver for the Atmel AT91RM9200 (Thunder)
 *
 * (c) SAN People (Pty) Ltd
 *
 * Based on an earlier Atmel EMAC macrocell driver by Atmel and Lineo Inc.
 * Initial version by Rick Bronson.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef AT91_ETHERNET
#define AT91_ETHERNET






#include "end.h"
#include "etherLib.h"
#include "miiLib.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* Ethernet Options */

#define ETH_FULL_DUPLEX                                     /* Support Full-Duplex */
#define ETH_AUTO_NEGOTIATION                                /* Enable Auto-Negotiation */
#define ETH_10BT                                            /* Support 10BaseT */


/* Ethernet Definitions */

#define ETH_DEV_NAME                    "eth"            /* device name */
#define ETH_DEV_NAME_LEN                4                   /* device name length (include terminating null) */
#define ETH_DEV_DESCRIPTION             "ATMEL AT91RM9200 Ethernet Enhanced Network Driver"

#define SIZE_ETH_ADDR                   6                   /* Ethernet Address Length */
#define SIZE_ETH_HDR                    14                  /* Ethernet Header Length */


/*#define SIZE_ETH_FB_HDR                 8*/                   /* Free Buffer Header */
#define SIZE_ETH_WA  					0

#if 0

#if     ((SIZE_ETH_HDR % 4) == 0)
#define SIZE_ETH_FB_HDR                 8                   /* Free Buffer Header */
#define SIZE_ETH_WA                     0                   /* Widget Align */
#elif   ((SIZE_ETH_HDR % 4) == 1)
#define SIZE_ETH_FB_HDR                 8                   /* Free Buffer Header */
#define SIZE_ETH_WA                     3                   /* Widget Align */
#elif   ((SIZE_ETH_HDR % 4) == 2)
#define SIZE_ETH_FB_HDR                 8                   /* Free Buffer Header */
#define SIZE_ETH_WA                     2                   /* Widget Align */
#else   /* ((SIZE_ETH_HDR % 4) == 3) */
#define SIZE_ETH_FB_HDR                 8                   /* Free Buffer Header */
#define SIZE_ETH_WA                     1                   /* Widget Align */
#endif  /* ((SIZE_ETH_HDR % 4) == 0) */

#endif

#define SIZE_ETH_CRC                    0                   /* CRC Length */
#define SIZE_ETH_MFLR                   (1500 + SIZE_ETH_HDR)   /* Max Ethernet Frame Length of Receive, exclude CRC */
#define SIZE_ETH_MINFLR                 (  46 + SIZE_ETH_HDR)   /* Min Ethernet Frame Length of Receive, exclude CRC */
#define SIZE_ETH_MDMA                   1524                /* Max DMA Length */


#define ETH_ALEN       SIZE_ETH_HDR
/* The following are all involved in forcing a particular link
 * mode for the device for setting things.  When getting the
 * devices settings, these indicate the current mode and whether
 * it was foced up into this mode or autonegotiated.
 */

/* The forced speed, 10Mb, 100Mb, gigabit, 10GbE. */
#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000
#define SPEED_10000		10000

/* Duplex, half or full. */
#define DUPLEX_HALF		0x00
#define DUPLEX_FULL		0x01

/* Which connector port. */
#define PORT_TP			0x00
#define PORT_AUI		0x01
#define PORT_MII		0x02
#define PORT_FIBRE		0x03
#define PORT_BNC		0x04

/* S3C2510 Ethernet Buffer Descriptor */
typedef struct recv_desc_bufs *PETHRBD, *PETHTBD;
 
#define MAX_ADDR_LEN 4
struct dev_mc_list
{	
	struct dev_mc_list	*next;
	UINT8			dmi_addr[MAX_ADDR_LEN];
	unsigned char		dmi_addrlen;
	int			dmi_users;
	int			dmi_gusers;
};
/* AT91 Ethernet Driver Control Structure */

typedef struct eth_drv_ctrl {
    END_OBJ         endObj;                                 /* base class */
    int             unit;                                   /* unit number */
    PHY_INFO        phyInfo;                                /* info on a MII-compliant PHY */
    FUNCPTR         receiveRtn;                             /* routine to call on reception */

    int irq;
  
#if 0 
   CL_POOL_ID      pClPool;                                /* pointer to the cluster pool */
#endif
    void           *pMblkArea;                              /* pointer to the mBlk/clBlk pool */
    void           *pClArea;                                /* pointer to the cluster pool */
 /*   void           *pBdArea;*/                                /* pointer to the buffer descriptor pool */
    int             clSize;                                 /* cluster pool size */

    BOOL            bPolling;                               /* TRUE if polling */
    BOOL            bTxBlocked;                             /* TRUE if tx is blocked */
    BOOL            bRxHandler;                             /* TRUE if rx handler is busy */
    BOOL            bTxHandler;                             /* TRUE if tx handler is busy */
    UINT16          l80225Status;                           /* L80225 Status Output Register */

    struct at91_private *priv;
    void* base_addr ;
    int mc_count;
    struct dev_mc_list* mc_list;
    int flags;
    char name[16];
	END_ERR	lastError;
} ETH_DRV_CTRL;





#define IFADDR                          endObj.mib2Tbl.ifPhysAddress
#define MIB2TBL                         endObj.mib2Tbl
#define PHYREGS                         phyInfo.miiRegs
#define dev_addr			IFADDR.phyAddress



#define MII_RTL8201BL_ID   0x00008201

/* Davicom 9161 PHY */
#define MII_DM9161_ID   0x0181b880

/* Davicom specific registers */
#define MII_DSCR_REG	16
#define MII_DSCSR_REG   17
#define MII_DSINTR_REG  21

/* Intel LXT971A PHY */
#define MII_LXT971A_ID	0x001378E0

/* Intel specific registers */
#define MII_ISINTE_REG	18
#define MII_ISINTS_REG	19

/* ........................................................................ */

#define MAX_RBUFF_SZ	0x604		/* 1518 rounded up +4  */ 
#define MAX_RX_DESCR	100		/* max number of receive buffers */

#define EMAC_DESC_DONE	0x00000001	/* bit for if DMA is done */
#define EMAC_DESC_WRAP	0x00000002	/* bit for wrap */

#define EMAC_BROADCAST	0x80000000	/* broadcast address */
#define EMAC_MULTICAST	0x40000000	/* multicast address */
#define EMAC_UNICAST	0x20000000	/* unicast address */
struct net_device_stats
{
	unsigned long	rx_packets;		/* total packets received	*/
	unsigned long	tx_packets;		/* total packets transmitted	*/
	unsigned long	rx_bytes;		/* total bytes received 	*/
	unsigned long	tx_bytes;		/* total bytes transmitted	*/
	unsigned long	rx_errors;		/* bad packets received		*/
	unsigned long	tx_errors;		/* packet transmit problems	*/
	unsigned long	rx_dropped;		/* no space in linux buffers	*/
	unsigned long	tx_dropped;		/* no space available in linux	*/
	unsigned long	multicast;		/* multicast packets received	*/
	unsigned long	collisions;

	/* detailed rx_errors: */
	unsigned long	rx_length_errors;
	unsigned long	rx_over_errors;		/* receiver ring buff overflow	*/
	unsigned long	rx_crc_errors;		/* recved pkt with crc error	*/
	unsigned long	rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long	rx_fifo_errors;		/* recv'r fifo overrun		*/
	unsigned long	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	unsigned long	tx_aborted_errors;
	unsigned long	tx_carrier_errors;
	unsigned long	tx_fifo_errors;
	unsigned long	tx_heartbeat_errors;
	unsigned long	tx_window_errors;
	
	/* for cslip etc */
	unsigned long	rx_compressed;
	unsigned long	tx_compressed;
};
struct rbf_t
{
	unsigned int addr;
	unsigned long size;
};

struct recv_desc_bufs
{
	struct rbf_t descriptors[MAX_RX_DESCR];		/* must be on sizeof (rbf_t) boundary */
	char recv_buf[MAX_RX_DESCR][MAX_RBUFF_SZ];	/* must be on long boundary */
};

typedef unsigned long dma_addr_t;
#define net_device eth_drv_ctrl
struct at91_private
{
	struct net_device_stats stats;
/*	struct mii_if_info mii;			 ethtool support */
	void * lock;  /* no use now */
	/* PHY */
	unsigned long phy_type;			/* type of PHY (PHY_ID) */

	short phy_media;			/* media interface type */

	/* Transmit */
	unsigned char * skb;			/* holds skb until xmit interrupt completes */
	unsigned char * skb_physaddr;		/* phys addr from pci_map_single */
	int skb_length;				/* saved skb length for pci_unmap_single */

	/* Receive */
	int rxBuffIndex;			/* index into receive descriptor list */

	struct recv_desc_bufs *dlist;		/* descriptor list address */
	struct recv_desc_bufs *dlist_phys;	/* descriptor list physical address */
	
};

   
/*#define NUM_TBD_ETH	             1 */



#include "mii.h"

#endif






