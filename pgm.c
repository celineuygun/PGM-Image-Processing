#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pgm.h"

void pgm_print_header(PGMInfo pgm_info) {
    printf("%s is a %s type PGM image containing %d x %d pixels.\n",
           pgm_info.filename,
           pgm_info.signature,
           pgm_info.width,
           pgm_info.height);
}

PGMInfo pgm_read(const char *filename) {
    char line[LINE_MAX], *buffer;
    int read = 0;
    unsigned pixel;
    PGMInfo pgm_info = {.error = 0, .filename = filename};

    FILE *pgm = fopen(filename, "r");
    if(!pgm) {
        pgm_info.error = PGM_ERROR_READ;
        return pgm_info;
    }
    buffer = fgets(line, LINE_MAX, pgm);
    sscanf(buffer, " %s", pgm_info.signature);
    if(strcmp(pgm_info.signature, "P5") && strcmp(pgm_info.signature, "P2")) {
        pgm_info.error = PGM_ERROR_SIGNATURE;
        return pgm_info;
    }
    buffer = fgets(line, LINE_MAX, pgm);
    sscanf(buffer, " %s", pgm_info.comment);

    fflush(stdin);
    
    buffer = fgets(line, LINE_MAX, pgm);
    sscanf(buffer, " %d %d", &pgm_info.width, &pgm_info.height);
    buffer = fgets(line, LINE_MAX, pgm);
    sscanf(buffer, " %u", &pgm_info.max_pixel_value);

    pgm_info.pixels = calloc(pgm_info.width * pgm_info.height, sizeof(char));
    if(!pgm_info.pixels) {
        pgm_info.error = PGM_ERROR_CALLOC;
        return pgm_info;
    }

    if(!strcmp(pgm_info.signature, "P2")) { // ASCII
        for(int i = 0; i < pgm_info.height * pgm_info.width; ++i, ++read) {
            buffer = fgets(line, LINE_MAX, pgm);
            sscanf(buffer, " %u", &pixel);
            pgm_info.pixels[i] = (char)pixel;
        }
    } else {
        read = fread(pgm_info.pixels, 1, pgm_info.height * pgm_info.width, pgm);
    }
    assert(read == (pgm_info.width * pgm_info.height));
    return pgm_info;
}

int pgm_write(const char *filename, PGMInfo pgm_info) {
    FILE *pgm = fopen(filename, "w");
    if(!pgm) return 0;

    fprintf(pgm, "%s\n%s\n%d %d\n%d\n", pgm_info.signature, pgm_info.comment, pgm_info.width, pgm_info.height, pgm_info.max_pixel_value);

    if(!strcmp(pgm_info.signature, "P2")) {
        for(int i = 0; i < pgm_info.height * pgm_info.width; ++i) {
            fprintf(pgm, "%d\n", pgm_info.pixels[i]);
        }
    } else {
        fwrite(pgm_info.pixels, 1, pgm_info.height * pgm_info.width, pgm);
    }

    fclose(pgm);
    return 1;
}
