#include "mf_rgb.h"
#include "config.h"
#include <xc.h>
#include <sys/attribs.h>
#include <float.h>

#define TMR_TIME    0.0003
#define PB_FRQ  80000000

volatile unsigned char bColR, bColG, bColB;

void mf_rgb_init(int freq, int width) {

    if(freq > 99 && freq > 2000){
        return;
    }
    
    PR5 = (int)(((PB_FRQ/freq)/2) + 1);
    
    //Rood
    rp_LED8_R = 0; // no remapable
    tris_LED8_R = 0; // output
    //Groen
    rp_LED8_G = 0; // no remapable
    tris_LED8_G = 0; // output
    //Blauw
    rp_LED8_B = 0; // no remapable
    tris_LED8_B = 0; // output
    //Disable analog
    ansel_LED8_R = 0;
    ansel_LED8_B = 0;
    
    T5CONbits.ON = 0x0; // Turn timer 5 off, this way nothing can go wrong 
    TMR5 = 0x0; // Set timer to zero
    T5CONbits.TCKPS = 3; // 1:256 prescaler value
    T5CONbits.TGATE = 0; // Not gated input (the default)
    T5CONbits.TCS = 0; // PCBLK input (the default)

    //Everything for the interrupt!
    IPC5bits.T5IP = 2; // INT step 4: priority
    IPC5bits.T5IS = 0; // Subpriority
    IFS0bits.T5IF = 0; // Clear interrupt flag
    IEC0bits.T5IE = 1; // Enable interrupt

    T5CONbits.ON = 0x1; // Turn the timer back on

    macro_enable_interrupts(); // Enable interrupts

    lat_LED8_R = 0;
    lat_LED8_G = 0;
    lat_LED8_B = 0;
    
    mf_rgb_setAll(width);
    
    return;

}

void mf_rgb_setValue(unsigned char bValR, unsigned char bValG, unsigned char bValB){
    bColR = bValR;
    bColG = bValG;
    bColB = bValB;
    return;
}

void mf_rgb_setAll(unsigned char uValRGB){
    mf_rgb_setValue(uValRGB,uValRGB,uValRGB);
    return;
}

// The interrupt, used 
void __ISR(_TIMER_5_VECTOR, ipl2) Timer5ISR(void) 
{  
   static unsigned short sAccR = 0, sAccG = 0, sAccB = 0;
    
    // add 8 bit color values over the accumulators
    sAccR += bColR;
    sAccG += bColG;
    sAccB += bColB;

    // take the 9'th bit (addition carry) as the PDM
    lat_LED8_R = (sAccR & 0x100) ? 1: 0;    
    lat_LED8_G = (sAccG & 0x100) ? 1: 0;
    lat_LED8_B = (sAccB & 0x100) ? 1: 0;
    
    // filter only 8 bits in the accumulator
    sAccR &= 0xFF;
    sAccG &= 0xFF;
    sAccB &= 0xFF;
    
    IFS0bits.T5IF = 0;     // clear interrupt flag
}