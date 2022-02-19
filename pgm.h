#ifndef _PGM_H_
#define _PGM_H_
#include <limits.h>

#define PGM_ERROR_READ          1
#define PGM_ERROR_SIGNATURE     2
#define PGM_ERROR_CALLOC        3

static char *pgm_error_messages[] = {
    NULL,
    "PGM Error: Couldn't read file",
    "PGM Error: Signature mismatch. Should be P2 or P5.",
    "PGM Error: calloc() error.",
};

#define pgm_print_error(p) fprintf(stderr, "%s\n", pgm_error_messages[p.error]);

typedef struct {
    const char *filename;
    char signature[3];
    char comment[LINE_MAX];
    int width;
    int height;
    unsigned max_pixel_value;
    unsigned char *pixels;
    int error;
} PGMInfo;

void pgm_print_header(PGMInfo pgm_info);
PGMInfo pgm_read(const char *filename);
int pgm_write(const char *filename, PGMInfo pgm_info);

#endif

