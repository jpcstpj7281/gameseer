/*======================================================================

    Device driver for the PCMCIA control functionality of Atmel
    AT91RM9200 microprocessor.
    
    (c) Rick Bronson

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License for the specific language governing
    rights and limitations under the License.

    The initial developer of the original code is John G. Dorsey
    <john+@cs.cmu.edu>.  Portions created by John G. Dorsey are
    Copyright (C) 1999 John G. Dorsey.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    case the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you do not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/
/*
 * Please see linux/Documentation/arm/SA1100/PCMCIA for more information
 * on the low-level kernel interface.
 */

#define AT91C_CF_PB0_CD1	AT91C_PIO_PB0	/* Compact Flash port pin aliases */
#define AT91C_CF_PB1_CD2	AT91C_PIO_PB1
#define AT91C_CF_PB2_IOIS16	AT91C_PIO_PB2	/* The access type (8 [high] or 16-bit [low])
						   is based on the state of the -IOIS16 signal */
#define AT91C_CF_PB3_STSCHG	AT91C_PIO_PB3
#define AT91C_CF_PB4_RDY	AT91C_PIO_PB4
#define AT91C_CF_PB5_RESET	AT91C_PIO_PB5
#define AT91C_CF_PB6_ENABLE	AT91C_PIO_PB6


#define AT91_PCMCIA_INC 0x10000000		/* increment value to go to next PCMCIA BASE */
#define AT91_PCMCIA_BASE(n) (0x50000000 + (AT91_PCMCIA_INC * n))
#define AT91_PCMCIA_A23 (1 << 23)		/* A23 is just A23 */
#define AT91_PCMCIA_REG (1 << 22)		/* REG is A22 */
#define AT91_PCMCIA_IO_BASE(n) (AT91_PCMCIA_BASE(n) | AT91_PCMCIA_A23)	/* io mode */
#define AT91_PCMCIA_CM_BASE(n) (AT91_PCMCIA_BASE(n) | AT91_PCMCIA_REG)	/* common memory mode */
#define AT91_PCMCIA_AT_BASE(n) AT91_PCMCIA_BASE(n)			/* attribute memory mode */

#define AT91_PCMCIA_MAX_SOCK 1
#define AT91_PCMCIA_POLL_PERIOD	55		/* debug only */
#define MAX_IO_WIN 2
#define AT91_PCMCIA_IO_ACCESS		(165)	/* in ns */
#define AT91_PCMCIA_3V_MEM_ACCESS	(150)	/* in ns */
#define AT91_PCMCIA_5V_MEM_ACCESS	(300)	/* in ns */

typedef unsigned long ioaddr_t;

struct pcmcia_configure {
  unsigned sock: 8,
            vcc: 8,
            vpp: 8,
          reset: 1,
            irq: 1;
};

struct pcmcia_state {
  unsigned detect: 1,
            ready: 1,
             bvd1: 1,	/* used for STSCHG only */
           iois16: 1,	/* 8/16 select */
           wrprot: 1,
            vs_3v: 1,
            vs_Xv: 1;
};
/* for GetSocket, SetSocket */
typedef struct socket_state_t {
    u_int	flags;
    u_int	csc_mask;
    u_char	Vcc, Vpp;
    u_char	io_irq;
} socket_state_t;
/* 
 * This structure encapsulates per-socket state which we might need to
 * use when responding to a Card Services query of some kind.
 */
struct at91_pcmcia_socket {
	/*
	 * Core PCMCIA state
	 */
	socket_state_t		cs_state;
/*	pccard_io_map		io_map[MAX_IO_WIN];
	pccard_mem_map		mem_map[MAX_WIN];
	void			(*handler)(void *, unsigned int);
	void			*handler_info;
*/
	struct pcmcia_state	k_state;
	ioaddr_t		phys_attr, phys_mem;
	void			*virt_io;

	/*
	 * Info from low level handler
	 */
	unsigned int		irq;
};

struct pcmcia_init {
	void (*handler)();
};



struct pcmcia_state_array {
	unsigned int size;
	struct pcmcia_state *state;
};

struct pcmcia_irq_info {
	unsigned int sock;
	unsigned int irq;
};

struct pcmcia_low_level {
	int (*init)(struct pcmcia_init *);
	int (*shutdown)(void);
	int (*socket_state)(struct pcmcia_state_array *);
	int (*get_irq_info)(struct pcmcia_irq_info *);
	int (*configure_socket)(const struct pcmcia_configure *);

	/*
	 * Enable card status IRQs on (re-)initialisation.  This can
	 * be called at initialisation, power management event, or
	 * pcmcia event.
	 */
	int (*socket_init)(int sock);

	/*
	 * Disable card status IRQs and PCMCIA bus on suspend.
	 */
	int (*socket_suspend)(int sock);
};

struct irqs {
	int irq;
/*	AT91PS_PIO base;*/
	int bits;
	const char *str;
};

extern struct irqs at91_pcmcia_irqs[];

extern struct pcmcia_low_level at91_pcmcia_ops;

#define MAX_IO_WIN 2

#define PC_3VCARD	0x1000
#define PC_XVCARD	0x2000
#define PC_PENDING	0x4000

/* InquireSocket capabilities */
#define PC_CAP_PAGE_REGS	0x0001
#define PC_CAP_VIRTUAL_BUS	0x0002
#define PC_CAP_MEM_ALIGN	0x0004
#define PC_CAP_STATIC_MAP	0x0008
#define PC_CAP_PCCARD		0x4000
#define PC_CAP_CARDBUS		0x8000

