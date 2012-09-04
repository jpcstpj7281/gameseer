/* at91IntrCtl.h - AT91RM9200 interrupt driver header file */




#ifndef __INCat91IntrCtlh
#define __INCat91IntrCtlh

#ifdef  __cplusplus
extern  "C" {
#endif


/* Interrupt Levels */

#define INT_LVL_FIQ           AT91C_ID_FIQ  
#define INT_LVL_SYS           AT91C_ID_SYS  
#define INT_LVL_PIOA          AT91C_ID_PIOA 
#define INT_LVL_PIOB          AT91C_ID_PIOB 
#define INT_LVL_PIOC          AT91C_ID_PIOC 
#define INT_LVL_PIOD          AT91C_ID_PIOD 
#define INT_LVL_US0           AT91C_ID_US0  
#define INT_LVL_US1           AT91C_ID_US1  
#define INT_LVL_US2           AT91C_ID_US2  
#define INT_LVL_US3           AT91C_ID_US3  
#define INT_LVL_MCI           AT91C_ID_MCI  
#define INT_LVL_UDP           AT91C_ID_UDP  
#define INT_LVL_TWI           AT91C_ID_TWI  
#define INT_LVL_SPI           AT91C_ID_SPI  
#define INT_LVL_SSC0          AT91C_ID_SSC0 
#define INT_LVL_SSC1          AT91C_ID_SSC1 
#define INT_LVL_SSC2          AT91C_ID_SSC2 
#define INT_LVL_TC0           AT91C_ID_TC0  
#define INT_LVL_TC1           AT91C_ID_TC1  
#define INT_LVL_TC2           AT91C_ID_TC2  
#define INT_LVL_TC3           AT91C_ID_TC3  
#define INT_LVL_TC4           AT91C_ID_TC4  
#define INT_LVL_TC5           AT91C_ID_TC5  
#define INT_LVL_UHP           AT91C_ID_UHP  
#define INT_LVL_EMAC          AT91C_ID_EMAC 
#define INT_LVL_IRQ0          AT91C_ID_IRQ0 
#define INT_LVL_IRQ1          AT91C_ID_IRQ1 
#define INT_LVL_IRQ2          AT91C_ID_IRQ2 
#define INT_LVL_IRQ3          AT91C_ID_IRQ3 
#define INT_LVL_IRQ4          AT91C_ID_IRQ4 
#define INT_LVL_IRQ5          AT91C_ID_IRQ5 
#define INT_LVL_IRQ6          AT91C_ID_IRQ6 





/* Interrupt Vectors */

#define INT_VEC_FIQ           INUM_TO_IVEC(INT_LVL_FIQ ) 
#define INT_VEC_SYS           INUM_TO_IVEC(INT_LVL_SYS )
#define INT_VEC_PIOA          INUM_TO_IVEC(INT_LVL_PIOA)
#define INT_VEC_PIOB          INUM_TO_IVEC(INT_LVL_PIOB)
#define INT_VEC_PIOC          INUM_TO_IVEC(INT_LVL_PIOC)
#define INT_VEC_PIOD          INUM_TO_IVEC(INT_LVL_PIOD)
#define INT_VEC_US0           INUM_TO_IVEC(INT_LVL_US0 )
#define INT_VEC_US1           INUM_TO_IVEC(INT_LVL_US1 )
#define INT_VEC_US2           INUM_TO_IVEC(INT_LVL_US2 )
#define INT_VEC_US3           INUM_TO_IVEC(INT_LVL_US3 )
#define INT_VEC_MCI           INUM_TO_IVEC(INT_LVL_MCI )
#define INT_VEC_UDP           INUM_TO_IVEC(INT_LVL_UDP )
#define INT_VEC_TWI           INUM_TO_IVEC(INT_LVL_TWI )
#define INT_VEC_SPI           INUM_TO_IVEC(INT_LVL_SPI )
#define INT_VEC_SSC0          INUM_TO_IVEC(INT_LVL_SSC0)
#define INT_VEC_SSC1          INUM_TO_IVEC(INT_LVL_SSC1)
#define INT_VEC_SSC2          INUM_TO_IVEC(INT_LVL_SSC2)
#define INT_VEC_TC0           INUM_TO_IVEC(INT_LVL_TC0 )
#define INT_VEC_TC1           INUM_TO_IVEC(INT_LVL_TC1 )
#define INT_VEC_TC2           INUM_TO_IVEC(INT_LVL_TC2 )
#define INT_VEC_TC3           INUM_TO_IVEC(INT_LVL_TC3 )
#define INT_VEC_TC4           INUM_TO_IVEC(INT_LVL_TC4 )
#define INT_VEC_TC5           INUM_TO_IVEC(INT_LVL_TC5 )
#define INT_VEC_UHP           INUM_TO_IVEC(INT_LVL_UHP )
#define INT_VEC_EMAC          INUM_TO_IVEC(INT_LVL_EMAC)
#define INT_VEC_IRQ0          INUM_TO_IVEC(INT_LVL_IRQ0)
#define INT_VEC_IRQ1          INUM_TO_IVEC(INT_LVL_IRQ1)
#define INT_VEC_IRQ2          INUM_TO_IVEC(INT_LVL_IRQ2)
#define INT_VEC_IRQ3          INUM_TO_IVEC(INT_LVL_IRQ3)
#define INT_VEC_IRQ4          INUM_TO_IVEC(INT_LVL_IRQ4)
#define INT_VEC_IRQ5          INUM_TO_IVEC(INT_LVL_IRQ5)
#define INT_VEC_IRQ6          INUM_TO_IVEC(INT_LVL_IRQ6)
                                                       
                                                       
                                                       
                                                       


#define NR_IRQS          32
#define AT91_INT_NUM_LEVELS NR_IRQS


/* Function Prototypes */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT void at91IntrInit(void);

#else  /* defined(__STDC__) || defined(__cplusplus) */

IMPORT void at91IntrInit();

#endif  /* defined(__STDC__) || defined(__cplusplus) */


#ifdef  __cplusplus
}
#endif

#endif  /* __INCat91IntrCtlh */
