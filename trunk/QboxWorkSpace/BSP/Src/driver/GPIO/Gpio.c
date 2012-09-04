/******************************************************************************


******************************************************************************/
#include "Gpio.h"


/* *****************************************************************************
                SOFTWARE API FOR PIO
   ***************************************************************************** */
/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgPeriph*/
/** \brief Enable pins to be drived by peripheral*/
/**----------------------------------------------------------------------------*/

 VOID BSP_AT91F_OR_PIO_CfgPeriphA(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPeriphAEnable
	)  /* \arg PERIPH B to enable*/

{
    DWORD dwTempValue;

    dwTempValue = spPio->PIO_ABSR;
    dwTempValue =  (~dwTempValue) | (1<<dwPeriphAEnable);
    spPio->PIO_ASR = dwTempValue;


	
    dwTempValue = spPio->PIO_PSR;
    dwTempValue =  (~dwTempValue) | (1<<dwPeriphAEnable);
    spPio->PIO_PDR = dwTempValue; /* Set in PIO mode*/

}




/* *****************************************************************************
                SOFTWARE API FOR PIO
   ***************************************************************************** */
/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgPeriph*/
/** \brief Enable pins to be drived by peripheral*/
/**----------------------------------------------------------------------------*/

 VOID BSP_AT91F_OR_PIO_CfgPeriphB(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPeriphBEnable
    )  /* \arg PERIPH B to enable*/

{
    DWORD dwTempValue;

    dwTempValue = spPio->PIO_ABSR;
    dwTempValue = dwTempValue | (1<<dwPeriphBEnable);
    spPio->PIO_BSR = dwTempValue;


	
    dwTempValue = spPio->PIO_PSR;
    dwTempValue =  (~dwTempValue) | (1<<dwPeriphBEnable);
    spPio->PIO_PDR = dwTempValue; /* Set in PIO mode*/




}


/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgOutput*/
/** \brief Enable PIO in output mode*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_CfgOutput(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPioEnable)      /* \arg PIO to be enabled*/
{
    DWORD dwTempValue;
    dwTempValue = spPio->PIO_PSR;
    dwTempValue = dwTempValue | (1<<dwPioEnable);
    spPio->PIO_PER = dwTempValue; /* Set in PIO mode*/
    dwTempValue = spPio->PIO_OSR;
    dwTempValue = dwTempValue | (1<<dwPioEnable);
    spPio->PIO_OER = dwTempValue; /* Configure in Output*/
}


/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgInput*/
/** \brief Enable PIO in input mode*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_CfgInput(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwInputEnable)      /* \arg PIO to be enabled*/
{
    /* Disable output*/
    
    DWORD dwTempValue;

    dwTempValue = spPio->PIO_PSR;
    dwTempValue = dwTempValue |  (1<<dwInputEnable);
    spPio->PIO_PER = dwTempValue; /* Set in PIO mode*/

	
    dwTempValue = spPio->PIO_OSR;
    dwTempValue =  (~dwTempValue) | (1<<dwInputEnable);
    spPio->PIO_ODR  = dwTempValue;

}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgOpendrain*/
/** \brief Configure PIO in open drain*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_CfgOpendrain(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwMultiDrvEnable) /* \arg pio to be configured in open drain*/
{
    /* Configure the multi-drive option*/
    spPio->PIO_MDDR = ~dwMultiDrvEnable;
    spPio->PIO_MDER = dwMultiDrvEnable;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgPullup*/
/** \brief Enable pullup on PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_CfgPullup(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPullupEnable)   /* \arg enable pullup on PIO*/
{
        /* Connect or not Pullup*/
    spPio->PIO_PPUER = dwPullupEnable;
}
 /**----------------------------------------------------------------------------*/
 /** \fn	BSP_AT91F_PIO_CfgPullup*/
 /** \brief Enable pullup on PIO*/
 /**----------------------------------------------------------------------------*/

 VOID BSP_AT91F_PIO_CfgPullupDisable(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPullupEnable)   /* \arg enable pullup on PIO*/
{
        /* Connect or not Pullup*/
    spPio->PIO_PPUDR = dwPullupEnable;

}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgDirectDrive*/
/** \brief Enable direct drive on PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_CfgdwDirectDrive(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwDirectDrive)    /* \arg PIO to be configured with direct drive*/

{
    /* Configure the Direct Drive*/
    spPio->PIO_OWDR  = ~dwDirectDrive;
    spPio->PIO_OWER  = dwDirectDrive;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgInputFilter*/
/** \brief Enable input filter on input PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_CfgInputFilter(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwInputFilter)    /* \arg PIO to be configured with input filter*/

{
    /* Configure the Direct Drive*/
    spPio->PIO_IFDR  = ~dwInputFilter;
    spPio->PIO_IFER  = dwInputFilter;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetInput*/
/** \brief Return PIO input value*/
/**----------------------------------------------------------------------------*/
  DWORD BSP_AT91F_OR_PIO_GetInput( /* \return PIO input*/
     AT91PS_PIO spPio,DWORD dwPeriphBEnable) /* \arg  pointer to a PIO controller*/
 {
    DWORD dwTempValue = spPio->PIO_PDSR;
  	dwTempValue =  dwTempValue & (1 << dwPeriphBEnable);
	dwTempValue = dwTempValue >>dwPeriphBEnable;
	return dwTempValue;
 }


 DWORD BSP_AT91F_PIO_GetInput( /* \return PIO input*/
    AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
    return spPio->PIO_PDSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsInputSet*/
/** \brief Test if PIO is input flag is active*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsInputSet(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  flag to be tested*/
{
    return (BSP_AT91F_PIO_GetInput(spPio) & dwFlag);
}


/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_SetOutput*/
/** \brief Set to 1 output PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_SetOutput(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  output to be set*/
{
    
    DWORD dwTempValue;
    dwTempValue = spPio ->PIO_ODSR;
    dwTempValue = dwTempValue | (1 << dwFlag );
    spPio->PIO_SODR = dwTempValue;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_ClearOutput*/
/** \brief Set to 0 output PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_ClearOutput(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  output to be cleared*/
{
    DWORD dwTempValue;
    dwTempValue = spPio ->PIO_ODSR;
    dwTempValue = ~dwTempValue | (1 << dwFlag );
    spPio->PIO_CODR = dwTempValue;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_ForceOutput*/
/** \brief Force output when Direct drive option is enabled*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_ForceOutput(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  output to be forced*/
{
    spPio->PIO_ODSR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_Enable*/
/** \brief Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_Enable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwInputEnable) /* \arg  pio to be enabled */
{
        spPio->PIO_PER = (1<<dwInputEnable);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_Disable*/
/** \brief Disable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_Disable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwInputEnable) /* \arg  pio to be disabled */
{
        spPio->PIO_PDR = (1<<dwInputEnable);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetStatus*/
/** \brief Return PIO Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetStatus( /* \return PIO Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_PSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsSet*/
/** \brief Test if PIO is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_OutputEnable*/
/** \brief Output Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_OutputEnable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio output to be enabled*/
{
        spPio->PIO_OER = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_OutputDisable*/
/** \brief Output Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_OutputDisable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio output to be disabled*/
{
        spPio->PIO_ODR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetOutputStatus*/
/** \brief Return PIO Output Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetOutputStatus( /* \return PIO Output Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_OSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsOuputSet*/
/** \brief Test if PIO Output is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsOutputSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetOutputStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_InputFilterEnable*/
/** \brief Input Filter Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_InputFilterEnable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio input filter to be enabled*/
{
        spPio->PIO_IFER = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_InputFilterDisable*/
/** \brief Input Filter Disable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_InputFilterDisable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio input filter to be disabled*/
{
        spPio->PIO_IFDR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetInputFilterStatus*/
/** \brief Return PIO Input Filter Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetInputFilterStatus( /* \return PIO Input Filter Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_IFSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsInputFilterSet*/
/** \brief Test if PIO Input filter is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsInputFilterSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetInputFilterStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetOutputDataStatus*/
/** \brief Return PIO Output Data Status */
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetOutputDataStatus( /* \return PIO Output Data Status */
    AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_ODSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_InterruptEnable*/
/** \brief Enable PIO Interrupt*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_InterruptEnable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio interrupt to be enabled*/
{
        spPio->PIO_IER = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_InterruptDisable*/
/** \brief Disable PIO Interrupt*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_InterruptDisable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio interrupt to be disabled*/
{
        spPio->PIO_IDR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetInterruptMaskStatus*/
/** \brief Return PIO Interrupt Mask Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetInterruptMaskStatus( /* \return PIO Interrupt Mask Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_IMR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetInterruptStatus*/
/** \brief Return PIO Interrupt Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetInterruptStatus( /* \return PIO Interrupt Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_ISR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsInterruptMasked*/
/** \brief Test if PIO Interrupt is Masked */
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsInterruptMasked(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetInterruptMaskStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsInterruptSet*/
/** \brief Test if PIO Interrupt is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsInterruptSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetInterruptStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_MultiDriverEnable*/
/** \brief Multi Driver Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_MultiDriverEnable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio to be enabled*/
{
        spPio->PIO_MDER = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_MultiDriverDisable*/
/** \brief Multi Driver Disable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_MultiDriverDisable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio to be disabled*/
{
        spPio->PIO_MDDR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetMultiDriverStatus*/
/** \brief Return PIO Multi Driver Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetMultiDriverStatus( /* \return PIO Multi Driver Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_MDSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsMultiDriverSet*/
/** \brief Test if PIO MultiDriver is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsMultiDriverSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetMultiDriverStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_A_RegisterSelection*/
/** \brief PIO A Register Selection */
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_A_RegisterSelection(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio A register selection*/
{
        spPio->PIO_ASR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_B_RegisterSelection*/
/** \brief PIO B Register Selection */
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_B_RegisterSelection(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio B register selection */
{
        spPio->PIO_BSR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_Get_AB_RegisterStatus*/
/** \brief Return PIO Interrupt Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_Get_AB_RegisterStatus( /* \return PIO AB Register Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_ABSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsAB_RegisterSet*/
/** \brief Test if PIO AB Register is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsAB_RegisterSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_Get_AB_RegisterStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_OutputWriteEnable*/
/** \brief Output Write Enable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_OutputWriteEnable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio output write to be enabled*/
{
        spPio->PIO_OWER = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_OutputWriteDisable*/
/** \brief Output Write Disable PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_PIO_OutputWriteDisable(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  pio output write to be disabled*/
{
        spPio->PIO_OWDR = dwFlag;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetOutputWriteStatus*/
/** \brief Return PIO Output Write Status*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetOutputWriteStatus( /* \return PIO Output Write Status*/
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_OWSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsOutputWriteSet*/
/** \brief Test if PIO OutputWrite is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsOutputWriteSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetOutputWriteStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_GetCfgPullup*/
/** \brief Return PIO Configuration Pullup*/
/**----------------------------------------------------------------------------*/
 DWORD BSP_AT91F_PIO_GetCfgPullup( /* \return PIO Configuration Pullup */
        AT91PS_PIO spPio) /* \arg  pointer to a PIO controller*/
{
        return spPio->PIO_PPUSR;
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsOutputDataStatusSet*/
/** \brief Test if PIO Output Data Status is Set */
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsOutputDataStatusSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (BSP_AT91F_PIO_GetOutputDataStatus(spPio) & dwFlag);
}

/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_IsCfgPullupStatusSet*/
/** \brief Test if PIO Configuration Pullup Status is Set*/
/**----------------------------------------------------------------------------*/
 int BSP_AT91F_PIO_IsCfgPullupStatusSet(
        AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
        DWORD dwFlag) /* \arg  flag to be tested*/
{
        return (~BSP_AT91F_PIO_GetCfgPullup(spPio) & dwFlag);
}


