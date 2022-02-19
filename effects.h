#ifndef _EFFECTS_H_
#define _EFFECTS_H_

void effect_invert(unsigned char *pixels, int width, int height);
void effect_binarize(unsigned char *pixels, int width, int height, int threshold);
void effect_random_noise(unsigned char *pixels, int width, int height);
void effect_smooth(unsigned char *pixels, int width, int height);
void effect_solarize(unsigned char *pixels, int width, int height, int threshold);

#endif
