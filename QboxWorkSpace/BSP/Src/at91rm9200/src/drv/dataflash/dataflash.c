/*----------------------------------------------------------------------------*/
/*         ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/*----------------------------------------------------------------------------*/
/* The software is delivered "AS IS" without warranty or condition of any*/
/* kind, either express, implied or statutory. This includes without*/
/* limitation any warranty or condition with respect to merchantability or*/
/* fitness for any particular purpose, or against the infringements of*/
/* intellectual property rights of others.*/
/*----------------------------------------------------------------------------*/
/* File Name           : dataflash.c*/
/* Object              : TEST DataFlash Functions*/
/* Creation            : FB   25/11/2002*/
/**/
/*----------------------------------------------------------------------------*/

#include "AT91C_SPI_DataFlash.h"

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_SpiWrite*/
/* \brief set the PDC registers for a transfert*/
/*----------------------------------------------------------------------------*/
static void AT91F_SpiWrite ( AT91PS_DataflashDesc pDesc )
{ 	int i;

   	pDesc->state = BUSY;


   	
   	AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTDIS + AT91C_PDC_RXTDIS;
   	
   	/* Initialize the Transmit and Receive Pointer*/
cacheFlush(DATA_CACHE,pDesc->tx_cmd_pt, pDesc->tx_cmd_size);
    AT91C_BASE_SPI->SPI_RPR = (unsigned int)pDesc->rx_cmd_pt ;
    AT91C_BASE_SPI->SPI_TPR = (unsigned int)pDesc->tx_cmd_pt ;

    /* Intialize the Transmit and Receive Counters*/
    AT91C_BASE_SPI->SPI_RCR = pDesc->rx_cmd_size ;
    AT91C_BASE_SPI->SPI_TCR = pDesc->tx_cmd_size ;

	if ( pDesc->tx_data_size != 0 )
   	{
	cacheFlush(DATA_CACHE,pDesc->tx_data_pt, pDesc->tx_data_size);
	   	/* Initialize the Next Transmit and Next Receive Pointer*/
    	AT91C_BASE_SPI->SPI_RNPR = (unsigned int)pDesc->rx_data_pt ;
	    AT91C_BASE_SPI->SPI_TNPR = (unsigned int)pDesc->tx_data_pt ;

		/* Intialize the Next Transmit and Next Receive Counters*/
	    AT91C_BASE_SPI->SPI_RNCR = pDesc->rx_data_size ;
	    AT91C_BASE_SPI->SPI_TNCR = pDesc->tx_data_size ;
   	}
    	
   	/* Enable RXBUFF Interrupt*/
    AT91C_BASE_SPI->SPI_IER = AT91C_SPI_RXBUFF;
//	for(i=0;i<10000;i++);
	AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTEN + AT91C_PDC_RXTEN;
	

}

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_DataFlashGetStatus*/
/* \brief Read the status register of the dataflash*/
/*----------------------------------------------------------------------------*/
AT91S_DataFlashStatus AT91F_DataFlashGetStatus(AT91PS_DataflashDesc pDesc)
{
	/* if a transfert is in progress ==> return 0	*/
	if( (pDesc->state) != IDLE)

		return DATAFLASH_BUSY;
	/* first send the read status command (D7H)*/
	pDesc->command[0] = DB_STATUS;
	pDesc->command[1] = 0;
	
	pDesc->DataFlash_state  = GET_STATUS;
    pDesc->tx_data_size 	= 0 ;	/* Transmit the command and receive response*/
    pDesc->tx_cmd_pt 		= pDesc->command ;
    pDesc->rx_cmd_pt 		= pDesc->command ;
    pDesc->rx_cmd_size 		= 2 ;
    pDesc->tx_cmd_size 		= 2 ;
    AT91F_SpiWrite (pDesc);
	
	return DATAFLASH_OK;
}

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_DataFlashHandler*/
/* \brief SPI Fixed Peripheral C interrupt handler.*/
/*----------------------------------------------------------------------------*/
void AT91F_DataFlashHandler(
	AT91PS_DataflashDesc pDesc,
	unsigned int status)
{
	/* If End of Receive Transfer interrupt occurred*/
    if (( status & AT91C_SPI_RXBUFF))
    {            
	    if( pDesc->state == BUSY)
        {
       		/* Next State*/
		pDesc->state = IDLE;
		cacheInvalidate(DATA_CACHE,pDesc->rx_cmd_pt, pDesc->rx_cmd_size);
		cacheInvalidate(DATA_CACHE,pDesc->rx_data_pt, pDesc->rx_data_size);
		if (pDesc->DataFlash_state == GET_STATUS)
			pDesc->DataFlash_state = *( (unsigned char *) (pDesc->rx_cmd_pt) +1);
        
        	/* Disable the Transmit Interrupt*/
        	AT91C_BASE_SPI->SPI_IDR = AT91C_SPI_RXBUFF;
        	AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTDIS + AT91C_PDC_RXTDIS;

        	return;
    	}	
    }          		
	pDesc->state = ERROR;
	AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTDIS + AT91C_PDC_RXTDIS;         
	AT91C_BASE_SPI->SPI_IDR = status;
}

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_DataFlashSendCommand*/
/* \brief Generic function to send a command to the dataflash*/
/*----------------------------------------------------------------------------*/
AT91S_DataFlashStatus AT91F_DataFlashSendCommand (
	AT91PS_DataFlash_Device pDataFlash,
	unsigned char OpCode,
	unsigned int CmdSize,
	unsigned int DataflashAddress)
{
    unsigned int adr;
	if ( (pDataFlash->pDataFlashDesc->state) != IDLE)
	{
		return DATAFLASH_BUSY;
	}	


				
	/* process the address to obtain page address and byte address*/
    adr = ((DataflashAddress / (pDataFlash->pDevice->pages_size)) << pDataFlash->pDevice->page_offset) + (DataflashAddress % (pDataFlash->pDevice->pages_size));

	/* fill the  command  buffer */
    pDataFlash->pDataFlashDesc->command[0] = OpCode;
    pDataFlash->pDataFlashDesc->command[1] = (unsigned char)((adr & 0x00FF0000) >> 16);
    pDataFlash->pDataFlashDesc->command[2] = (unsigned char)((adr & 0x0000FF00) >> 8);
    pDataFlash->pDataFlashDesc->command[3] = (unsigned char)(adr & 0x000000FF) ;
    pDataFlash->pDataFlashDesc->command[4] = 0;
    pDataFlash->pDataFlashDesc->command[5] = 0;
    pDataFlash->pDataFlashDesc->command[6] = 0;
    pDataFlash->pDataFlashDesc->command[7] = 0;
    
	/* Initialize the SpiData structure for the spi write fuction */
    pDataFlash->pDataFlashDesc->tx_cmd_pt   =  pDataFlash->pDataFlashDesc->command ;	
    pDataFlash->pDataFlashDesc->tx_cmd_size =  CmdSize ;
    pDataFlash->pDataFlashDesc->rx_cmd_pt   =  pDataFlash->pDataFlashDesc->command ;
    pDataFlash->pDataFlashDesc->rx_cmd_size =  CmdSize ;

	/* send the command and read the data */
    AT91F_SpiWrite (pDataFlash->pDataFlashDesc);

	return DATAFLASH_OK;
}

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_DataFlashPageRead*/
/* \brief Main memory page read*/
/*----------------------------------------------------------------------------*/
AT91S_DataFlashStatus AT91F_DataFlashPageRead (
	AT91PS_DataFlash_Device pDataFlash,
	unsigned int src,
	unsigned char *dataBuffer,
	int sizeToRead )
{
    pDataFlash->pDataFlashDesc->rx_data_pt = dataBuffer ;	/* buffer for the read operation*/
    pDataFlash->pDataFlashDesc->rx_data_size = sizeToRead;	/* Number of byte to read*/
    pDataFlash->pDataFlashDesc->tx_data_pt = dataBuffer ;
    pDataFlash->pDataFlashDesc->tx_data_size = sizeToRead;

	/* Send the command to the dataflash*/
	return (AT91F_DataFlashSendCommand (pDataFlash, DB_PAGE_READ, 8, src));
}

/*----------------------------------------------------------------------------*/
/* \fn    AT91F_DataFlashPagePgmBuf*/
/* \brief Main memory page program through buffer 1 or buffer 2*/
/*----------------------------------------------------------------------------*/
AT91S_DataFlashStatus AT91F_DataFlashPagePgmBuf(
	AT91PS_DataFlash_Device pDataFlash,
	unsigned char *src,
	unsigned int dest,
	unsigned int SizeToWrite)
{	
    pDataFlash->pDataFlashDesc->tx_data_pt = src ;
    pDataFlash->pDataFlashDesc->tx_data_size = SizeToWrite ;
    pDataFlash->pDataFlashDesc->rx_data_pt = src;
    pDataFlash->pDataFlashDesc->rx_data_size = SizeToWrite;

	/* Send the command to the dataflash */
	return(AT91F_DataFlashSendCommand (pDataFlash, DB_PAGE_PGM_BUF1, 4, dest));
}



