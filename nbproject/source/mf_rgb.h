//We'll use timer5 for the PWM signal
//

#ifndef _MF_RGB_H_

#define _MF_RGB_H

#include <xc.h>
#include "assignment1_6.h"

/* ================================================================= */
/* function: rgbled_init */
/* */
/* description: initialises the RGB LED connected to OC3 (R), OC5 (G)*/
/* and OC4 (B) at a given width each. The repetition */
/* frequency of the PWM signals can be set using the */
/* freq argument. */
/* */
/* pre: freq ? repetition frequency of the PWM signals in Hz. */
/* The range of frequencies is 100 Hz ? 2 kHz. */
/* width ? default width of the 3 channels in %. */
/* */
/* post: none */
/* ================================================================= */
void mf_rgb_init(int, int);

/* ================================================================= */
/* function: rgbled_setpwmwidths */
/* */
/* description: sets the PWM widths for each of the channels of the */
/* RGB LED. */
/* */
/* pre: rwidth ? width of the R channel in %. */
/* gwidth ? width of the G channel in %. */
/* bwidth ? width of the B channel in %. */
/* */
/* post: none */
/* ================================================================= */
void mf_rgb_setValue(unsigned char bValR, unsigned char bValG, unsigned char bValB);

void mf_rgb_setAll(unsigned char uValRGB);
#endif