#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pgm.h"
#include "effects.h"

#define THRESHOLD 130

int main(int argc, char *argv[]) {
    char effect_name[20];
    const char fileloc[] = "effect_images/", extension[] = "pgm";
    char file[50], newfile[50];

    if(argc < 2) {
        printf("\nUsage: ./pgm_effect <PGM image 1> ... <PGM image N>\n");
        exit(1);
    } 
    for(int i = 1; i < argc; ++i) {
        while(strstr(argv[i], extension)){
            printf("\nPlease enter the file names without the extension.\n");
            exit(1);
        }
    }
    PGMInfo pgm_info;
    srand(time(NULL));

    printf("\nSelect an effect you want to apply.\nEffects available: binarize, noise, smooth, invert, solarize\n>> ");
    scanf(" %s", effect_name);
    while(strcmp(effect_name, "binarize") && strcmp(effect_name, "noise") && strcmp(effect_name, "smooth") && strcmp(effect_name, "invert") && strcmp(effect_name, "solarize")) {
        printf("\nPlease select a valid one.\n>> ");
        scanf(" %s", effect_name);
    } 
    
    printf("\n===== PROCESSED IMAGES\n");
    for(int i = 1; i < argc; ++i) {
        sprintf(file, "%s%s.%s", fileloc, argv[i], extension);
        sprintf(newfile, "%s%s_%s.%s", fileloc, argv[i], effect_name, extension);

        pgm_info = pgm_read(file);
        if(pgm_info.error != 0) {
            pgm_print_error(pgm_info);
            exit(1);
        }
        pgm_print_header(pgm_info);
        
        if(!strcmp(effect_name, "invert"))
            effect_invert(pgm_info.pixels, pgm_info.width, pgm_info.height);
        else if(!strcmp(effect_name, "binarize"))
            effect_binarize(pgm_info.pixels, pgm_info.width, pgm_info.height, THRESHOLD);
        else if(!strcmp(effect_name, "noise"))
            effect_random_noise(pgm_info.pixels, pgm_info.width, pgm_info.height);
        else if(!strcmp(effect_name, "smooth"))
            effect_smooth(pgm_info.pixels, pgm_info.width, pgm_info.height);
        else if(!strcmp(effect_name, "solarize"))
            effect_solarize(pgm_info.pixels, pgm_info.width, pgm_info.height, THRESHOLD);

        if(!pgm_write(newfile, pgm_info)) {
            printf("Error while writing PMG file.\n");
        }
        free(pgm_info.pixels);
    } return 0;
}
