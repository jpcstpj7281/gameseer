	


Component INCLUDE_MMC {
	NAME		AT91RM9200 MMC drive
	SYNOPSIS	AT91RM9200 MMC drive component

	CONFIGLETTES	usrMMC.c 
	INIT_RTN	mmcDrv ();
	HDR_FILES	drv/mmc/mmcDrv.h
	_CHILDREN FOLDER_PERIPHERALS
	_INIT_ORDER usrIosExtraInit
}

Component INCLUDE_SPI_DATAFLASH_CARD {
	NAME		AT91RM9200 SPI DataFlash Card drive
	SYNOPSIS	AT91RM9200 SPI DataFlash Card drive component

	CONFIGLETTES	usrDataFlash.c 
	INIT_RTN	dataflashDrv ();
	HDR_FILES	drv/dataFlash/dataflashDrv.h
	_CHILDREN FOLDER_PERIPHERALS
	_INIT_ORDER usrIosExtraInit
}

Component INCLUDE_DISPLAY {
	NAME		EPSON s1d13xxx drive
	SYNOPSIS	EPSON s1d13xxx(on AT91RM9200) display drive component

	INIT_RTN	at91_s1d1xInit();
	HDR_FILES	drv/display/at91display.h
	_CHILDREN FOLDER_PERIPHERALS
	_INIT_ORDER usrIosExtraInit
}


Component INCLUDE_USB_SLAVE_BULK {
	NAME		AT91RM9200 USB slave driver
	SYNOPSIS	AT91RM9200 USB slave bulk transfer driver
	
	INIT_RTN	at91UsbSlaveInit();
	HDR_FILES	drv/usbslave/at91UsbSlave.h
	_CHILDREN FOLDER_PERIPHERALS
	_INIT_ORDER usrIosExtraInit
}

Component INCLUDE_SOUND_CODEC {
	NAME		DAC3550a Codec on AT91RM9200EK 
	SYNOPSIS	DAC3550a Codec driver for AT91RM9200EK
	
	INIT_RTN	dac3550Drv();
	HDR_FILES	drv/audio/dac3550drv.h
	_CHILDREN FOLDER_PERIPHERALS
	_INIT_ORDER usrIosExtraInit
}



