#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "effects.h"

void effect_random_noise(unsigned char *pixels, int width, int height) {
    int nr_noisy_pixel = (width * height) / 5; // %5 oraninda noise ekle

    for (int i = 0; i < nr_noisy_pixel; ++i ) {
        int which_pixel = (rand() % (width * height));
        pixels[which_pixel] = (rand() % 256);
    }
}

void effect_invert(unsigned char *pixels, int width, int height) {
    for(int i = 0; i < width * height; ++i)
        pixels[i] = 255 - pixels[i];
}

void effect_binarize(unsigned char *pixels, int width, int height, int threshold) {
    for(int i = 0; i < width * height; ++i) {
        if(pixels[i] > threshold) pixels[i] = 255;
        else pixels[i] = 0;
    }
}

void effect_smooth(unsigned char *pixels, int width, int height) {
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            int sum = 0, counter = 0;
            for(int k = -1; k < 2; ++k) {
                for(int l = -1; l < 2; ++l) {
                    if((i + k) * width + (j + l) < 0 || (i + k) * width + (j + l) >= height * width) continue;
                    if((j % width == 0 && l == -1) || (j % width == (width - 1) && l == 1)) continue;
                    sum += pixels[(i + k) * width + j + l];
                    counter++;
                }
            } pixels[i * width + j] = sum / counter;
        }
    }
}

void effect_solarize(unsigned char *pixels, int width, int height, int threshold) {
    for(int i = 0; i < width * height; ++i) {
        if(pixels[i] > threshold)
            effect_invert(&pixels[i], 1, 1);
    }
}
