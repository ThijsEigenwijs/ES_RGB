/** Descriptive File Name

  @Company
    Fontys Hogenscholen Eindhoven
    Engineering
    Thijs Tops
    356791@student.fontys.nl
    Github: https://github.com/thijseigenwijs

  @File Name
   mf_timers.h

  @Summary
    This file is the file where i do everything related to timers. The code file
 *  makes everything working, with code and stuff, done with #ifdef to save
 *  space on the controller

  @Description
    This file contains everything i need, so yeah....
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include "mf_timer.h"

void mf_timer1_init() {
    
    OC3CONCLR = 0X8000; //  Turn off OC1 
    OC3CONCLR = 0X0006; // clearing OCM bits
    OC3CONCLR = 0x0008; //Bit3:Timer2 is used for the generation of PWM frequency
    // The value of OC3RS will be loaded into OC1R at the beginning of new cycle
    OC3RS = (PR2 + 1) / 2; // duty cycle = OC1RS/(PR2+1) = 50%
    OC3CONCLR = 0X08; // Bit3:Timer2 is used for the generation of PWM frequency
    OC3CONSET = 0X0006; // PWM mode without fault pin; 
    // OC3CONSET = 6<<0;
    OC3CONSET = 0X8000; //  Turn OC1 ON
    
    T1CONbits.ON = 0x0; //Turing the timer off
    T1CONbits.TCS = 0;
    T1CONbits.TGATE = 1;
    T1CONbits.TCKPS = 3; //Setting the presale
    PR1 = 65534; //Setting the timer
    T1CONbits.ON = 0x1; //Enable the timer
    TMR1 = 0;
}
