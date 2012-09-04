/**--------------------------------------------------------------------------------------*/
/**      ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**--------------------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**--------------------------------------------------------------------------------------*/
/** File Name           : TWI ICS1523 driver*/
/** Object              :*/
/** Translator          :*/
/** 1.0 08/30/02 ED		: Creation*/
/** 1.2 13/01/03 FB		: Update on lib V3*/
/**--------------------------------------------------------------------------------------*/

#include	"ics1523.h"
#include	"AT91RM9200.h"
#include	"lib_AT91RM9200.h"

/********************************************************************************/
/* Externals*/
/********************************************************************************/


/********************************************************************************/
/* Global Variables*/
/********************************************************************************/

/** Supported standard configurations*/
const AT91S_ICS1523Desc Param_conf_list[] =
{
	/** TFT_Conf Definition File Parameters*/
	{
		( ICS_ENDLS | ICS_ENPLS | ICS_PDEN ),
		( ICS_PSD | ICS_PFD ),
		0x39,
		0x00,
		0x00,
		0x03,
		( ICS_OEF | ICS_OET2 | ICS_OETCK ),
		( ICS_INSEL | 0x7F )
	}
} ;

/** ICS1523 Parameters Descriptor*/
AT91S_ICS1523Desc ICS1523_Desc ;

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_SetTwiClock*/
/** \brief Initialization*/
/**----------------------------------------------------------------------------*/
void AT91F_SetTwiClock(const AT91PS_TWI pTwi,unsigned int mck_khz)
{
	int sclock;

	/* Here, CKDIV = 1 and CHDIV=CLDIV  ==> CLDIV = CHDIV = 1/4*((Fmclk/FTWI) -6)*/

	sclock = (10*mck_khz /ICS_TRANSFER_RATE);
	if (sclock % 10 >= 5)
		sclock = (sclock /10) - 5;
	else
		sclock = (sclock /10)- 6;
	sclock = (sclock + (4 - sclock %4)) >> 2;	/* div 4*/

    pTwi->TWI_CWGR	= 0x00010000 | sclock | (sclock << 8);
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_ICS1523_Init*/
/** \brief Initialization of the Clock Generator ICS1523*/
/**----------------------------------------------------------------------------*/
int AT91F_ICS1523_Init (unsigned int conf, unsigned int mck_khz)
{
	int 			ack,nb_trial,error_status ;
	char *			status ;
	unsigned int	initial_timeout;

	error_status = (int) ICS1523_ACCESS_OK ;

	/** Descriptors initialisation*/
	ICS1523_Desc.icr = Param_conf_list[conf].icr ;
	ICS1523_Desc.lcr = Param_conf_list[conf].lcr ;
	ICS1523_Desc.fd0 = Param_conf_list[conf].fd0 ;
	ICS1523_Desc.fd1 = Param_conf_list[conf].fd1 ;
	ICS1523_Desc.dpao = Param_conf_list[conf].dpao ;
	ICS1523_Desc.dpac = Param_conf_list[conf].dpac ;
	ICS1523_Desc.oes = Param_conf_list[conf].oes ;
	ICS1523_Desc.odr = Param_conf_list[conf].odr ;

	/* Configure TWI PIOs*/
	AT91F_TWI_CfgPIO ();
	AT91F_PIO_CfgOpendrain(AT91C_BASE_PIOA,(unsigned int) AT91C_PA25_TWD);

	/* Configure PMC by enabling TWI clock*/
	AT91F_TWI_CfgPMC ();
	
	/* Configure TWI in master mode*/
	AT91F_TWI_Configure (AT91C_BASE_TWI);
	
	/* Set TWI Clock Waveform Generator Register	*/
	AT91F_SetTwiClock(AT91C_BASE_TWI,mck_khz);

	/* ICS1523 Initialisation*/
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_ICR, ( unsigned char ) 0 ) ;
	error_status |= ack ;
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_OE, ( unsigned char ) ICS1523_Desc.oes ) ;
	error_status |= ack ;
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_OD, ( unsigned char ) ICS1523_Desc.odr ) ;
	error_status |= ack ;
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_DPAO, ( unsigned char ) 0 ) ;
	error_status |= ack ;
	
	nb_trial = 0 ;
	do
	{
		nb_trial++ ;
		ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_ICR, ( unsigned char ) ICS1523_Desc.icr ) ;
		error_status |= ack ;
		ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_LCR, ( unsigned char ) ICS1523_Desc.lcr ) ;
		error_status |= ack ;
		ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_FD0, ( unsigned char ) ICS1523_Desc.fd0 ) ;
		error_status |= ack ;
		ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_FD1, ( unsigned char ) ICS1523_Desc.fd1 ) ;
		error_status |= ack ;
		ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_SWRST, ( unsigned char ) ( ICS_PLLR ) ) ;
		error_status |= ack ;

	    /* Program 1ms temporizing period*/
		initial_timeout = AT91F_GetTickCount();
		while( AT91F_GetTickCount() < (initial_timeout + TIMEOUT_OF_1000us) );

		AT91F_ICS1523_ReadByte ( ( unsigned char ) ICS_SR, status ) ;
	} while ( !( ( unsigned int ) *status & ( unsigned int ) ICS_PLLLOCK ) && ( nb_trial < 10 ) ) ;
	
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_DPAC, ( unsigned char ) ICS1523_Desc.dpac ) ;
	error_status |= ack ;
	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_SWRST, ( unsigned char ) ( ICS_DPAR ) ) ;
	error_status |= ack ;
	
	/** Program 1ms temporizing period*/
	initial_timeout = AT91F_GetTickCount();
	while( AT91F_GetTickCount() < (initial_timeout + TIMEOUT_OF_1000us) );

	ack = AT91F_ICS1523_WriteByte ( ( unsigned char ) ICS_DPAO, ( unsigned char ) ICS1523_Desc.dpao ) ;
	error_status |= ack ;
	return ( error_status ) ;
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_ICS1523_WriteByte*/
/** \brief Write a byte with TWI Interface to the Clock Generator ICS1523*/
/**----------------------------------------------------------------------------*/
int AT91F_ICS1523_WriteByte (char reg_address, char data_out)
{
	int 			Status, nb_trial ;
	unsigned int	initial_timeout;

    AT91C_BASE_TWI->TWI_MMR = (AT91C_TWI_MREAD & 0x0) | AT91C_TWI_IADRSZ_1_BYTE | ((ICS_ADD << 0x10) & AT91C_TWI_DADR);
	AT91C_BASE_TWI->TWI_IADR = ( unsigned int ) reg_address ;
	AT91C_BASE_TWI->TWI_THR	= ( unsigned int ) data_out ;
    AT91C_BASE_TWI->TWI_CR = ( unsigned int ) ( AT91C_TWI_START | AT91C_TWI_STOP ) ;

	/** Program temporizing period (300us)*/
	initial_timeout = AT91F_GetTickCount();
	while( AT91F_GetTickCount() < initial_timeout + TIMEOUT_OF_300us);

    nb_trial = 0 ;
    Status = AT91C_BASE_TWI->TWI_SR ;

    while ( !( Status  & AT91C_TWI_TXCOMP ) && ( nb_trial < 10 ) )
    {
		nb_trial++;
		if ( Status  & AT91C_TWI_ERROR )
		{	
		/* Si Under run OR NACK Start again*/
	    AT91C_BASE_TWI->TWI_CR	= ( unsigned int ) ( AT91C_TWI_START | AT91C_TWI_STOP ) ;
		/** Program temporizing period (300us)*/
		initial_timeout = AT91F_GetTickCount();
		while( AT91F_GetTickCount() < (initial_timeout + TIMEOUT_OF_300us) );
		}
		Status = AT91C_BASE_TWI->TWI_SR ;
    };
    
	if (Status & AT91C_TWI_TXCOMP)
		return ( (int) ICS1523_ACCESS_OK ) ;
	else
		return ( (int) ICS1523_ACCESS_ERROR ) ;
}

/**----------------------------------------------------------------------------*/
/** \fn    AT91F_ICS1523_ReadByte*/
/** \brief Read a byte with TWI Interface from the Clock Generator ICS1523*/
/**----------------------------------------------------------------------------*/
int AT91F_ICS1523_ReadByte (char reg_address, char *data_in)
{
	int 			Status, nb_trial ;
	unsigned int	initial_timeout;

    AT91C_BASE_TWI->TWI_MMR = AT91C_TWI_MREAD | AT91C_TWI_IADRSZ_1_BYTE | ((ICS_ADD << 0x10) & AT91C_TWI_DADR);
    AT91C_BASE_TWI->TWI_IADR = ( unsigned int ) reg_address ;
	AT91C_BASE_TWI->TWI_CR = ( unsigned int ) ( AT91C_TWI_START | AT91C_TWI_STOP ) ;

	/** Program temporizing period (300us)*/
	initial_timeout = AT91F_GetTickCount();
	while( AT91F_GetTickCount() < (initial_timeout + TIMEOUT_OF_300us) );

	nb_trial = 0 ;
    Status = AT91C_BASE_TWI->TWI_SR ;

	/** Wait TXcomplete ...*/
    while ( !( Status  & AT91C_TWI_TXCOMP ) && ( nb_trial < 10 ) )
    	{
    	nb_trial++;
		Status = AT91C_BASE_TWI->TWI_SR ;
		}
		
	if (Status & AT91C_TWI_TXCOMP)
	{
		*data_in = (char) AT91C_BASE_TWI->TWI_RHR ;
		return ( (int) ICS1523_ACCESS_OK ) ;
	}
	return ( (int) ICS1523_ACCESS_ERROR ) ;
}
