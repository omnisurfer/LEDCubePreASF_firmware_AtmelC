/*
 * sysclk.c
 *
 * Created: 7/19/2015 2:34:40 PM
 *  Author: Daniel
 */ 

#include "sysclk.h"

extern void InitSysClk(void)
{
	/* PLL Enable (Page 78)
	To enable the PLL, the following procedure must be followed:
	1. Enable reference clock source.
	2. Set the multiplication factor and select the clock reference for the PLL.
	3. Wait until the clock reference source is stable.
	4. Enable the PLL.
	*/
	
	//(App note AVR1003) Unlock clock changes (CCP), Set to 32MHz, DFLL to internal 32KHz ref and enable		
	//Website assistance: 
	//http://morf.lv/modules.php?name=tutorials&lasit=28
	//http://www.avrfreaks.net/forum/setting-pll-and-external-clock
	
	OSC.CTRL |= OSC_RC32MEN_bm;
	
	//wait for osc to stabilize
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
					
	OSC.DFLLCTRL |= OSC_RC32MCREF0_bm;
	
	OSC.DFLLCTRL |= DFLL_ENABLE_bm;
	
	//PLLSRC to 32MHz, Unlock PLL changes, Scale to x1
	OSC.PLLCTRL = (OSC.PLLCTRL & ~OSC_PLLSRC_gm) | OSC_PLLSRC_RC32M_gc;
	
	//32MHz OSC / 4 = 8MHz SYSCLK. 8MHz SYSCLK * 4 (PLL MULT) = 32MHz SYSCLK
	OSC.PLLCTRL = (OSC.PLLCTRL & ~OSC_PLLFAC_gm) | (OSC_PLLFAC_gm & 0x04);
		
	//enable PLL
	OSC.CTRL |= OSC_PLLEN_bm;
	
	while(!(OSC.STATUS & OSC_PLLRDY_bm));
	
	//Set clock to PLL
	CCP = CCP_IOREG_gc;
	
	CLK.CTRL = CLK_SCLKSEL_PLL_gc;
}