/* 
 * File:   assignment1_6.c
 * Author: thijs
 *
 * Created on 6 oktober 2017, 13:20
 */

// PIC32MX370F512L Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_16         // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_1       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = OFF             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT           // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Enabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is Disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Port Enabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>

#include "assignment1_6.h"
#include "mf_rgb.h"

unsigned int POT_Value();

int main() {

    //
    mf_rgb_init(1000,50);
    mf_timer1_init();
   
    //Config SW0
    TRISFbits.TRISF3 = 1;



    int colorFade = 0;
    int colorPercentage = 0;

    PR1 = 312 * 2;

    while (1) {

        if (TMR1 > (PR1 / 2)) {

            TMR1 = 0;

            colorPercentage = colorPercentage + 1;
            if (colorPercentage == 101) { colorPercentage = colorPercentage + 1;
                colorPercentage = 0;
                colorFade = colorFade + 1;
                if (colorFade == 14)
                    colorFade = 0;
            }

            switch (colorFade) {
                case 0:
                    mf_rgb_setValue(0,0,colorPercentage);
                    break;
                case 1:
                    mf_rgb_setValue(0,0,(100-colorPercentage));
                    break;
                case 2:
                    mf_rgb_setValue(0,colorPercentage,colorPercentage);
                    break;
                case 3:
                    mf_rgb_setValue(0,100-colorPercentage,100-colorPercentage);
                    break;
                case 4:
                    mf_rgb_setValue(0,colorPercentage,0);
                    break;
                case 5:
                    mf_rgb_setValue(0,100-colorPercentage,0);
                    break;
                case 6:
                    mf_rgb_setValue(colorPercentage,colorPercentage,0);
                    break;
                case 7:
                    mf_rgb_setValue(100-colorPercentage,100-colorPercentage,0);
                    break;
                case 8:
                    mf_rgb_setValue(colorPercentage,0,0);
                    break;
                case 9:
                    mf_rgb_setValue(100-colorPercentage,0,0);
                    break;
                case 10:
                    mf_rgb_setValue(colorPercentage,0,colorPercentage);
                    break;
                case 11:
                    mf_rgb_setValue(100-colorPercentage,0,100-colorPercentage);
                    break;
                case 12:
                    mf_rgb_setAll(colorPercentage);
                    break;
                case 13:
                    mf_rgb_setAll(100-colorPercentage);
                    break;
                    
                          
                        
                    
                    
                default:
                    mf_rgb_setAll(0);
                    break;

            }
        }
    }
    return 1;
}
