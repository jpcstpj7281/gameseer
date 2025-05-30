/*
 *  linux/drivers/at91/usb/at91_usb_ohci-at91.c
 *
 *  (c) Rick Bronson
 *
 *  The outline of this code was taken from Brad Parkers <brad@heeltoe.com>
 *  original OHCI driver modifications, and reworked into a cleaner form
 *  by Russell King <rmk@arm.linux.org.uk>.
 */

#include "AT91RM9200_UHP.h"

/*
  NOTE:
  The following is so that we don't have to include usb-ohci.h or pci.h as the
  usb-ohci.c driver needs these routines even when the architecture
  has no PCI bus...
*/
/*
extern int  hc_add_ohci(struct pci_dev *dev, int irq, void *membase,
	    unsigned long flags, void *ohci, const char *name,
	    const char *slot_name);

extern void hc_remove_ohci(void *ohci);
*/
static void *at91_ohci;
AT91PS_UHP ohci_regs;

static int  at91_ohci_init(void)
{
	int ret;

	ohci_regs = (AT91PS_UHP)AT91_UHP_BASE ; /*ioremap(AT91_UHP_BASE, SZ_4K);*/


	/* Enable PLLB */
	AT91_SYS->CKGR_PLLBR = AT91_PLLB_INIT;
	while ((AT91_SYS->PMC_SR & 4) == 0);

	/* Now, enable the USB clock */
	AT91_SYS->PMC_SCER = AT91C_PMC_UHP;	/* enable system clock */
	AT91_SYS->PMC_PCER = 1 << AT91C_ID_UHP;	/* enable peripheral clock */

	/* Take Hc out of reset */
	ohci_regs->UHP_HcControl = 2 << 6;
#if 0
	/* Initialise the generic OHCI driver. */
	ret = hc_add_ohci((struct pci_dev *) 1, AT91C_ID_UHP,
			  (void *)ohci_regs, 0, &at91_ohci,
			  "usb-ohci", "at91");
	if (ret)
		iounmap(ohci_regs);
#endif
	return ret;
}

static void  at91_ohci_exit(void)
{
/*	hc_remove_ohci(at91_ohci); */

	/* Force UHP_Hc to reset */
	ohci_regs->UHP_HcControl = 0;

	 /* Stop the USB clock. */
	AT91_SYS->PMC_SCDR = AT91C_PMC_UHP;	/* disable system clock */
	AT91_SYS->PMC_PCDR = 1 << AT91C_ID_UHP;	/* disable peripheral clock */

	/*iounmap(ohci_regs);*/
}


