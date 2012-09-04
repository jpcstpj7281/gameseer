/* sysWindML.c - WindML BSP specific routines  */

/* Copyright 2001 Wind River Systems, Inc. */

#include "copyright_wrs.h"
/*
modification history
--------------------
01a,07aug01,m_h  created
*/

#include <vxWorks.h>
#include <ugl/sysWindML.h>
#include <config.h>
#include <pciClass.h>
#include "at91rm9200dk.h"

/*
DESCRIPTION

This library provides board-specific routines to support WindML.  This file is 
included at the end of sysLib.c when WindML functionality is to be included.

This API is designed in a general fashion, such that it is applicable to all
processor types and is bus independent.  It provides the support equally for
graphics devices that are integral to a processor (such as with the PPC821) 
and graphics devices that are present on a PCI bus.

The API provides support for configurations where a system has multiple graphics
devices and input devices.

A data structure allocated within the BSP provides information describing the 
graphics, input (keyboard and pointer), and audio devices.  A serial pointer
that connects to a standard serial port (such as, /tyCo/0) is not covered by
this API.  Those devices use the standard serial drivers.

The data structure to define the graphics device is as follows:

 typedef struct windml_device
   {
    UINT32  vendorID,                   /@ vendor ID @/
    UINT32  deviceID,                   /@ device ID @/
    UINT32  instance,                   /@ instance of device @/
    UINT32  devType,                    /@ type of input device @/
    UINT32  regDelta;                   /@ distance between adjacent registers @/
    UINT32  intLevel;                   /@ interrupt level to be used @/
    VOIDFUNCPTR * intVector;            /@ interrupt vector to be used @/
    void    * pPhysBaseAdrs0;           /@ first base address @/
    void    * pPhysBaseAdrs1;           /@ second base address @/
    void    * pPhysBaseAdrs2;           /@ third base address @/
    void    * pPhysBaseAdrs3;           /@ fourth base address @/
    void    *pRegBase;                  /@ base address of register space @/
   } WINDML_DEVICE;


 The above structure provides space for up to two memory segments that are used
 to access the device (for example, one segment for the frame buffer
 and another for the memory mapped registers).  Typically, a device 
 will only have a single memory segment.  The size field identifies the number
 of bytes present within the memory segment.

 The <pRegBase> field identifies the base address to use to access the I/O ports.
 This is typically the base of the ISA space.  For X86 type processors, this
 field would be set to 0.  For powerPC processors, this field would be set 
 according to the memory model used (PRep or CHRP).

INCLUDE FILES: ugl/sysWindML.h
*/

/******************************************************************************
*
* sysWindMLDevGet - configures the device
*
* This routine will determine the presence of the device and perform any device 
* configuration required.  The behaviour of this function varies depending on the 
* type of device configuration (such as a PCI device, integral, device 
* controller, etc.).  A device configuration data structure is created for the 
* specified device.  This configuration data defines the access mechanism for 
* the device.    
*
* The <vendorID> and <deviceID> identify the vendor and device identifiers in
* the PCI environment.  If these values are set to zero, then the <instance> 
* occurrence of a device will be returned.  For example, if the <instance> and 
* <vendorID> were set to zero, then the routine will return the first occurrence 
* of a device.
* 
* The returned data structure provides miscellaneous data items that describe 
* the manner in which to access the device.  
*
* RETURNS: When device has been successfully configured, the address of the
*          device data structure; otherwise NULL
*
*/

WINDML_DEVICE * sysWindMLDevGet 
    (
    UINT32 devType,     /* Device Type */
    UINT32 instance,	/* The instance of the device */
    UINT32 vendorID,	/* The identifier for the device manufacturer */
    UINT32 deviceID	/* The identifier for the device */
    )
    {
    WINDML_DEVICE * pDev = NULL;
    int busno, slotno, funcno;
    UINT16 data;
    UINT32 memRgn = 0; /* set only to silence compiler warning */

    switch (devType) {
	case WINDML_GRAPHICS_DEVICE :
	    {
#if 0
	    if (vendorID == 0 || deviceID == 0)
		{
		int pciClass = PCI_CLASS_DISPLAY_CTLR << 16;

		if (pciFindClass (pciClass, instance, &busno, &slotno, &funcno) != OK)
		    {
		    return (pDev);
		    }

		if (pciConfigInWord (busno, slotno, funcno, PCI_CFG_VENDOR_ID,
                                     (short *)&data)
		    != OK)
		    {
		    return (pDev);
		    }

		vendorID = data;

		if (pciConfigInWord (busno, slotno, funcno, PCI_CFG_DEVICE_ID,
                                     (short *) &data)
		    != OK)
		    {
		    return (pDev);
		    }

		deviceID = data;
		}
	    else
		{
		if (pciFindDevice (vendorID, deviceID, instance, 
				   &busno, &slotno, &funcno) != OK) 
		    {
		    return (pDev);
		    }
		}

	    pDev = (WINDML_DEVICE *)calloc(1, sizeof(WINDML_DEVICE));

	    if (pDev == NULL)
		{
		return (pDev);
		}

            /* Assign resources (interrupt, I/O) */
            
            pciAssignResources (busno, slotno, funcno);

	    /* extract base address from config space */

	    if (pciConfigInLong (busno, slotno, funcno, 
                                 PCI_CFG_BASE_ADDRESS_0, (int *)&memRgn) != OK)
                {
                return NULL;
                }

            memRgn  &= PCI_MEMBASE_MASK;
#else
	    pDev = (WINDML_DEVICE *)calloc(1, sizeof(WINDML_DEVICE));
#endif
	    pDev->vendorID = vendorID;
	    pDev->deviceID = deviceID;
	    pDev->instance = instance;
	    pDev->devType = devType;
	    pDev->pPhysBaseAdrs0 = (void *) memRgn;
	    pDev->pPhysBaseAdrs1 = 0;
	    pDev->pPhysBaseAdrs2 = 0;
	    pDev->pPhysBaseAdrs3 = 0;
	    pDev->regDelta = 0;
	    pDev->intLevel = 0;
	    pDev->intVector = NULL;
	    pDev->pRegBase = 0;

	    break;
	    }

	case WINDML_KEYBOARD_DEVICE :
	    {
	    pDev = (WINDML_DEVICE *)calloc(1, sizeof(WINDML_DEVICE));

	    if (pDev == NULL)
		{
		return (pDev);
		}

	    pDev->devType = devType;
	    pDev->instance = 0;
	    pDev->regDelta = 4;
	    pDev->intLevel = INT_LVL_KEYBOARD;
	    pDev->intVector = (VOIDFUNCPTR *)INT_VEC_KEYBOARD;
	    pDev->pRegBase = (void *)KBD_BASE_ADR;

	    break;
	    }

	case WINDML_POINTER_DEVICE :
	    {
	    pDev = (WINDML_DEVICE *)calloc(1, sizeof(WINDML_DEVICE));

	    if (pDev == NULL)
		{
		return (pDev);
		}

	    pDev->devType = devType;
	    pDev->instance = 0;
	    pDev->regDelta = 4;
	    pDev->intLevel = INT_LVL_MOUSE;
	    pDev->intVector = (VOIDFUNCPTR *)INT_VEC_MOUSE;
	    pDev->pRegBase = (void *)MOUSE_BASE_ADR;

	    break;
	    }

	case WINDML_AUDIO_DEVICE :
            {
            /* not implemented yet */
	    break;
	    }

	default:
	    {
	    break;
	    }
	}
    return (pDev);
    }

/******************************************************************************
*
* sysWindMLDevCtrl - special control of the device mode
*
* This routine provides special control features for the device.  This
* function is essentially a catch all to provide control of the device
* where the functionality is provided within a PCI configuration header or
* by board specific registers which may be shared by other functions implemented
* on the target board.
*
* The <function> argument defines the type of function that is to be performed
* and the <pArg> parameter provides the details relating to the function. 
*
* The values for <function> and the interpretation of the <pArg> parameters are:
*
*\is
*\i WINDML_ACCESS_MODE_SET
*       Sets the device's access mode as to whether it is to respond to I/O
*       cycles of memory mapped cycles or both.  The accessibility is provided
*       by the <pArg> parameter which is bit mapped containing the flags
*       WINDML_MEM_ENABLE (enable memory mapped access) and WINDML_IO_ENABLE 
*	(enable I/O access).
*\i WINDML_LCD_MODE_SET
*       Sets the control mode for an LCD that is controllable by an on board
*       register rather than a graphics device register. The mode information
*	is passed through <pArg>. The flags available are WINDML_LCD_ON
*	WINDML_LCD_OFF, WINDML_BACKLIGHT_ON, WINDML_BACKLIGHT_OFF.
*\i WINDML_BUSWIDTH_SET
*	Some boards allow the LCD bus width to be changed dynamically via
*	an FPGA or other configurable logic. This can be done in a board
* 	specific manner. The actual bus width will be passed through <pArg>.
*\ie
*
* RETURNS: OK when control operation was success; otherwise ERROR
*
*/

STATUS sysWindMLDevCtrl 
    (
    WINDML_DEVICE *pDev,	/* Device to control */
    int function,		/* Type of operation to perform */
    int *pArg			/* Control mode */
    )
    {
    STATUS status = ERROR;

    if (pDev == NULL)
	{
	return(status);
	}

    switch (function)
	{
	case WINDML_ACCESS_MODE_SET:
	    {
	    int busno, slotno, funcno;

	    if (pciFindDevice (pDev->vendorID, 
			       pDev->deviceID, 
			       pDev->instance, 
			       &busno, &slotno, &funcno) != OK) 
		{
		return (ERROR);
		}

	    status = pciConfigOutWord(busno, slotno, funcno, 
				      PCI_CFG_COMMAND, *pArg);
	    break;
	    }

	default:
	    {
	    break;
	    }
	}
    return(status);
    }

/******************************************************************************
*
* sysWindMLDevRelease - release a device configuration
*
* This routine will release any resources that were allocated when a  
* device was configured using the <sysWindMLDevGet()> function.  This 
* function will free the memory that was allocated for the WINDML_DEVICE 
* data structure is it were dynamically allocated.  If the data structure was not 
* dynamically allocated, this function will usually be simply a stub.
*
* RETURNS: OK when  operation was success; otherwise ERROR
*
*/

STATUS sysWindMLDevRelease 
    (
    WINDML_DEVICE *pDev	/* Device to release */
    )
    {
    if(pDev != NULL)
	free(pDev);

    return(OK);
    }

/******************************************************************************
*
* sysWindMLIntConnect - Connect the device interrupt.
*
* This routine connects a routine to the interrupt.
*
* RETURNS: OK or ERROR
*/

STATUS sysWindMLIntConnect
    (
    WINDML_DEVICE *pDev,	/* Graphics device to control */
    VOIDFUNCPTR   routine,      /* routine to be called */
    int           parameter     /* parameter to be passed */
    )
    {
    STATUS status = ERROR;

    if (pDev != NULL && pDev->intVector != NULL && routine != NULL)
	{
	if (pDev->devType == WINDML_AUDIO_DEVICE)
	    {
	    status = pciIntConnect(pDev->intVector, routine, parameter);
	    }
	else
	    {
	    status = intConnect (pDev->intVector, routine, parameter);
	    }
	}
    return (status);
    }

/******************************************************************************
*
* sysWindMLIntEnable - Enable interrupts.
*
* This routine enables the interrupt.
*
* RETURNS: OK or ERROR
*/

STATUS sysWindMLIntEnable
    (
    WINDML_DEVICE *pDev	/* Device to control */
    )
    {
    STATUS status = ERROR;

    if (pDev != NULL && pDev->intLevel != 0)
	{
	if (pDev->devType != WINDML_AUDIO_DEVICE)
	    {
	    status = intEnable (pDev->intLevel);
	    }
	else
	    {
	    status = OK;
	    }
	}

    return (status);
    }

/******************************************************************************
*
* sysWindMLIntDisable - Disable interrupts.
*
* This routine disables the interrupt.
*
* RETURNS: OK or ERROR
*/

STATUS sysWindMLIntDisable
    (
    WINDML_DEVICE *pDev	/* Device to control */
    )
    {
    STATUS status = ERROR;

    if(pDev != NULL && pDev->intLevel != 0)
	{
	if (pDev->devType != WINDML_AUDIO_DEVICE)
	    {
	    status = intDisable (pDev->intLevel);
	    }
	else
	    {
	    status = OK;
	    }
	}

    return (status);
    }

/*******************************************************************************
*
* sysWindMLHwInit - Perform any necessary hardware initialization in sysHwInit()
*
* RETURNS: OK or ERROR
*/
STATUS sysWindMLHwInit
    (
    void
    )
    {
    printf ("sysWindMLHwInit\n");

    return(OK);
    }

