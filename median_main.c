#include <stdio.h>
#include <stdlib.h>

#include "pgm.h"

#define N_IMAGES 9

void swap(unsigned char *arr, int i, int j);
int partition(unsigned char* arr, int l, int r);
void quick_sort(unsigned char* arr, int l, int r);
unsigned char sort_and_get_median(unsigned char *pixels, int size);

int main(int argc, const char *argv[]) {
    const char fileloc[] = "median_images/", extension[] = "pgm";
    char file[50], newfile[50];
    PGMInfo images[N_IMAGES];
    PGMInfo filtered;
    unsigned char pixels[N_IMAGES];

    printf("\n===== PROCESSED IMAGES\n");
    for(int i = 0; i < N_IMAGES; ++i) {
        sprintf(file, "%s%d.%s", fileloc, i + 1, extension);
        if(i == 1)
            filtered = pgm_read(file);
        images[i] = pgm_read(file);
        if(images[i].error != 0) {
            pgm_print_error(images[i]);
            exit(1);
        } pgm_print_header(images[i]);
    }

    for(int i = 0; i < filtered.width * filtered.height; ++i) {
        for(int j = 0; j < N_IMAGES; ++j)
            pixels[j] = images[j].pixels[i];
        filtered.pixels[i] = sort_and_get_median(pixels, N_IMAGES);
    }
    
    sprintf(newfile, "%sfiltered.%s", fileloc, extension);
    if(!pgm_write(newfile, filtered)) {
            printf("Error while writing PMG file.\n");
    }

    printf("\n===== FILE NAMED '%s' IS CREATED.\n", newfile);

    for(int i = 0; i < N_IMAGES; ++i)
        free(images[i].pixels);
    free(filtered.pixels);
    return 0;
}

void swap(unsigned char *arr, int i, int j) {
   unsigned char temp = arr[i];
   arr[i] = arr[j];
   arr[j] = temp;
}

int partition(unsigned char* arr, int l, int r) {
    unsigned char pivot = arr[r];
    int i = l - 1, j = l;
    for(; j < r; ++j) {
        if(arr[j] < pivot) {
            ++i;
            swap(arr, i, j);
        }
    } swap(arr, i + 1, r);
    return (i + 1);
}

void quick_sort(unsigned char* arr, int l, int r) {
    if(l >= r) return;
    int p = partition(arr, l, r);
    quick_sort(arr, l, p - 1);
    quick_sort(arr, p + 1, r);
}

unsigned char sort_and_get_median(unsigned char *pixels, int size) {
    quick_sort(pixels, 0, size - 1);
    return pixels[(size - 1) / 2];
}