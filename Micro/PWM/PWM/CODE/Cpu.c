/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.C
**     Project   : PWM
**     Processor : MC56F8257
**     Component : 56F8257
**     Version   : Component 01.014, Driver 02.08, CPU db: 3.00.231
**     Datasheet : MC56F824x/5xPB Rev. 1.0.0, 09/2008; MC56F82XXRM Rev. 0 Draft A 11/2008
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012-12-02, ���� 5:19
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**
**     (c) Freescale Semiconductor
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Cpu. */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"


/* Global variables */
volatile word SR_lock = 0;             /* Lock */
volatile word SR_reg;                  /* Current value of the SR register */
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component 56F8257)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma interrupt alignsp
void Cpu_Interrupt(void)
{
  asm(DEBUGHLT);                       /* Halt the core and placing it in the debug processing state */
}

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component 56F8257)
**
**     Description :
**         Disables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component 56F8257)
**
**     Description :
**         Enables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component 56F8257)
**
**     Description :
**         Sets low power mode - Stop mode.
**         For more information about the stop mode see this CPU
**         documentation.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component 56F8257)
**
**     Description :
**         Sets low power mode - Wait mode.
**         For more information about the wait mode see this CPU
**         documentation.
**         Release from wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  _EntryPoint (component 56F8257)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void init_56800_(void);         /* Forward declaration of external startup function declared in startup file */

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

void _EntryPoint(void)
{
  #pragma constarray off

  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/

  /*** ### MC56F8257 "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  /* System clock initialization */
  setRegBitGroup(OCCS_OSCTL, TRIM, (word)getReg(FM_OPT0) & 0x03FF); /* Set the trim osc freq with factory programmed value */
  setRegBit(OCCS_OSCTL, CLK_MODE);     /* Select an internal oscillator mode */
  clrRegBit(OCCS_CTRL, PRECS);         /* Select an internal clock source for the CPU core */
  setReg(OCCS_CTRL, (OCCS_CTRL_LCKON_MASK | OCCS_CTRL_ZSRC0_MASK)); /* Enable PLL, LCKON and select clock source from prescaler */
  /* OCCS_DIVBY: LORTP=2,COD=0,??=0,PLLDB=0x1D */
  setReg16(OCCS_DIVBY, 0x201DU);       /* Set the clock prescalers */ 
  while(!getRegBit(OCCS_STAT, LCK0)){} /* Wait for PLL lock */
  setReg(OCCS_CTRL, (OCCS_CTRL_LCKON_MASK | OCCS_CTRL_ZSRC1_MASK)); /* Select clock source from postscaler */
  /* FM_CLKDIV: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DIVLD=0,PRDIV8=0,DIV=0x28 */
  setReg16(FM_CLKDIV, 0x28U);          /* Set the flash clock prescaler */ 
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

  setReg(COP_CTRL, 0);                 /* Disable COP running after reset */
  asm(JMP init_56800_);                /* Jump to C startup code */
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component 56F8257)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* SIM_SD0: TA0=0,TA1=0,TA2=0,TA3=0,TB0=0,TB1=0,TB2=0,TB3=0,ADC=0,GPIOA=0,GPIOB=0,GPIOC=0,GPIOD=0,GPIOE=0,GPIOF=0,??=0 */
  setReg16(SIM_SD0, 0x00U);            /* Set up the STOP disable register 0 */ 
  /* SIM_SD1: ??=0,DAC=0,CMPA=0,CMPB=0,CMPC=0,SCI0=0,SCI1=0,QSPI0=0,IIC0=0,IIC1=0,CRC=0,REFA=0,REFB=0,REFC=0,??=0,MSCAN=0 */
  setReg16(SIM_SD1, 0x00U);            /* Set up the STOP disable register 1 */ 
  /* SIM_SD2: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,PWMCH0=0,PWMCH1=0,PWMCH2=0,PWMCH3=0 */
  setReg16(SIM_SD2, 0x00U);            /* Set up the STOP disable register 2 */ 
/* Enable peripheral clock */
  /* SIM_PCE1: HFM=1,MSCAN=1 */
  setReg16Bits(SIM_PCE1, 0x03U);       /* Enable prph.clocks in the SIM_PCE1 register before Common initialization */ 
  /* GPIO_A_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE7=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_A_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOA pins according to the CPU bean settings */ 
  /* GPIO_B_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE7=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_B_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOB pins according to the CPU bean settings */ 
  /* GPIO_C_DRIVE: DRIVE15=0,DRIVE14=0,DRIVE13=0,DRIVE12=0,DRIVE11=0,DRIVE10=0,DRIVE9=0,DRIVE8=0,DRIVE7=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_C_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOC pins according to the CPU bean settings */ 
  /* GPIO_D_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_D_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOD pins according to the CPU bean settings */ 
  /* GPIO_E_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE7=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_E_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOE pins according to the CPU bean settings */ 
  /* GPIO_F_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE8=0,DRIVE7=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,DRIVE3=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_F_DRIVE, 0x00U);       /* Set High/Low drive strength on GPIOF pins according to the CPU bean settings */ 
  /* SIM_PCR: TMRA_CR=0,TMRB_CR=0,SCI0_CR=0,SCI1_CR=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg16(SIM_PCR, 0x00U);            /* Set the TMR; TMRB; QSCI0; QSCI1 module clock rates */ 
  /* SIM_CTRL: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,ONCEEBL=0,SWRST=0,STOP_DISABLE=0,WAIT_DISABLE=0 */
  setReg16(SIM_CTRL, 0x00U);           /* Set up the SIM control register */ 
  /* SIM_CLKOUT: ??=0,??=0,??=1,??=0,??=0,??=0,??=0,??=0,??=0,TEST=0,CLKDIS=1,CLKOSEL=0 */
  setReg16(SIM_CLKOUT, 0x2020U);       /* Set up the SIM clock output select register */ 
  /* Disable peripheral clock after initialization of their registers (if the clocks should not be enabled in init. code) */
  /* SIM_PCE0: TA0=0,TA1=0,TA2=0,TA3=0,TB0=0,TB1=0,TB2=0,TB3=0,ADC=0,GPIOA=0,GPIOB=0,GPIOC=0,GPIOD=0,GPIOE=0,GPIOF=0,??=0 */
  setReg16(SIM_PCE0, 0x00U);           /* Disable prph.clocks in the SIM_PCE0 register after Common initialization */ 
  /* SIM_PCE1: ??=0,DAC=0,CMPA=0,CMPB=0,CMPC=0,SCI0=0,SCI1=0,QSPI0=0,IIC0=0,IIC1=0,CRC=0,REFA=0,REFB=0,REFC=0 */
  clrReg16Bits(SIM_PCE1, 0xFFFCU);     /* Disable prph.clocks in the SIM_PCE1 register after Common initialization */ 
  /* SIM_PCE2: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,PWMCH0=0,PWMCH1=0,PWMCH2=0,PWMCH3=0 */
  setReg16(SIM_PCE2, 0x00U);           /* Disable prph.clocks in the SIM_PCE2 register after Common initialization */ 
  __EI(0);                             /* Enable interrupts of the selected priority level */
}

/* END Cpu. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
