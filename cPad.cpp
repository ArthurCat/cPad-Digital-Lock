#include <stdint.h>
#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Menu.h"
#include "HAL_Wheel.h"
#include "LPM.h"
#include "PMM.h"
#include "Demo_Cube.h"
#include "CTS_Layer.h"
#include "stdlib.h"
#include "captp.h"

static const char *const capMenuText[] = {
    "=Arthur's Design=",
    "1.Set Password",
    "2.Electronic Lock",
    "3.Low Power",

};
char *itoa(int, char *, int);

// Forward Declared Function
void Alsney(void);
void set(void);
void lowpower(void);
void MenuLPM(void);
int8_t passwords[6];
int8_t setkey[6];



void captp(void)
{
	   uint8_t selection = 0;

	    buttonsPressed = 0;

	    Dogs102x6_clearScreen();

	    Dogs102x6_stringDraw(7, 0, "*S1=Enter S2=Esc*", DOGS102x6_DRAW_NORMAL);
	    selection = Menu_active((char **)capMenuText, 3);
	    if (buttonsPressed & BUTTON_S2);
	    else
	       switch (selection)
	        {
                case 1: set();   break;
                case 2: cPad();break;
                case 3: lowpower();break;
	            default: break;
	        }
}


void cPad(void)
{

    uint8_t sliderPosition = 0,i = 0;
    for(i=0;i<6;i++)
    {
    	passwords[i]=0;
    }
    Board_ledOff(LED_ALL);                           
    Dogs102x6_clearScreen();
    buttonsPressed = 0;

    Dogs102x6_stringDraw(1, 0, "  Put Finger on ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 0, "   Touch Pads    ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 0, " Enter Passwords", DOGS102x6_DRAW_NORMAL);

    TI_CAPT_Init_Baseline(&slider);                 

    while (!(buttonsPressed & BUTTON_S2))           
    {
        sliderPosition = TI_CAPT_Slider(&slider);

        sliderPosition = (sliderPosition + 10) / 20;   
        //ÒÔÏÂ ¸ù¾Ý´¥Ãþ°´¼üÎ»ÖÃµãÁÁÏàÓ¦LED
        switch (sliderPosition)
        {
            case 0: Board_ledOff(LED4 + LED5 + LED6 + LED7 + LED8);
                    for(i=0;i<6;i++)
                    {
                    	passwords[i]=0;
                    }
                break;
            case 1: Board_ledToggle(LED4);
		    passwords[0]=!passwords[0];
                __delay_cycles(5000000);
                break;
            case 2: Board_ledToggle(LED5);
		    passwords[1]=!passwords[1];
                __delay_cycles(5000000);
                break;
            case 3: Board_ledToggle(LED6);
		    passwords[2]=!passwords[2];
                __delay_cycles(5000000);
                break;
            case 4: Board_ledToggle(LED7);
		    passwords[3]=!passwords[3];
                __delay_cycles(5000000);
                break;
            case 5: Board_ledToggle(LED8);
		    passwords[4]=!passwords[4];
                __delay_cycles(5000000);
                break;
            case (255 / 17):
                break;
        }
	if((passwords [0]==setkey[0])&&(passwords [1]==setkey[1])&&(passwords [2]==setkey[2])
			&&(passwords [3]==setkey[3])&&(passwords [4]==setkey[4]))//ÄÚÖÃÃÜÂë
	{
         Dogs102x6_stringDraw(5, 0, "     RIGHT ", DOGS102x6_DRAW_NORMAL);
         Board_ledOff(LED1+LED2+LED3);
	}
	else
	{
         Dogs102x6_stringDraw(5, 0, "     WRONG ", DOGS102x6_DRAW_NORMAL);
         Board_ledOn(LED1+LED2+LED3);
	}
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonsPressed = 0;
    lab2();

    Dogs102x6_setBacklight(0x00);

}


void set(void)
{
    uint8_t sliderPosition = 0,i = 0;
    for(i=0;i<6;i++)
    {
    	setkey[i]=0;
    }
    Board_ledOff(LED_ALL);                          
    Dogs102x6_clearScreen();
    buttonsPressed = 0;

    Dogs102x6_stringDraw(1, 0, "  Put Finger on ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 0, "   Touch Pads    ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 0, " Set Passwords", DOGS102x6_DRAW_NORMAL);

    TI_CAPT_Init_Baseline(&slider);                 

    while (!(buttonsPressed & BUTTON_S1))           
    {
        sliderPosition = TI_CAPT_Slider(&slider);

        sliderPosition = (sliderPosition + 10) / 20;    

        switch (sliderPosition)
        {
            case 0: Board_ledOff(LED4 + LED5 + LED6 + LED7 + LED8);
                    for(i=0;i<6;i++)
                    {
                    	setkey[i]=0;
                    }
                break;
            case 1: Board_ledToggle(LED4);
		    setkey[0]=!setkey[0];
                __delay_cycles(5000000);
                break;
            case 2: Board_ledToggle(LED5);
            setkey[1]=!setkey[1];
                __delay_cycles(5000000);
                break;
            case 3: Board_ledToggle(LED6);
            setkey[2]=!setkey[2];
                __delay_cycles(5000000);
                break;
            case 4: Board_ledToggle(LED7);
            setkey[3]=!setkey[3];
                __delay_cycles(5000000);
                break;
            case 5: Board_ledToggle(LED8);
            setkey[4]=!setkey[4];
                __delay_cycles(5000000);
                break;
            case (255 / 17):
                break;
        }
    }
        Board_ledOff(LED_ALL);
        Dogs102x6_clearScreen();
        buttonsPressed=0;
        lab2();
}




void lowpower(void)
{
    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(3, 0, " Low Power Mode", DOGS102x6_DRAW_NORMAL);
    while(!(buttonsPressed & BUTTON_S2))
    {
       Dogs102x6_setBacklight(0x00);
    }
    Dogs102x6_setBacklight(0xff);
    buttonsPressed = 0;
}
  /*  #pragma vector = UNMI_VECTOR
    __interrupt void UNMI_ISR(void)
    {
        switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
        {
            case SYSUNIV_NONE:
                __no_operation();
                break;
            case SYSUNIV_NMIIFG:
                __no_operation();
                break;
            case SYSUNIV_OFIFG:
                UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT2OFFG); // Clear OSC flaut Flags fault flags
                SFRIFG1 &= ~OFIFG;                          // Clear OFIFG fault flag
                break;
            case SYSUNIV_ACCVIFG:
                __no_operation();
                break;
            case SYSUNIV_BUSIFG:
                // If bus error occurred - the cleaning of flag and re-initializing of USB is required.
                SYSBERRIV = 0;                              // clear bus error flag
               // USB_disable();                              // Disable
        }
    }

*/

