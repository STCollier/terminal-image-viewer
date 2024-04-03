#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Image {
    int width, height, channels;
    unsigned char* texture;
};

struct Image image_new(const char* path) {
    struct Image image;

    image.texture = stbi_load(path, &image.width, &image.height, &image.channels, 0);

    if (!image.texture) {
        fprintf(stderr, "Failed to load image %s", path);
        exit(EXIT_FAILURE);
    }

    return image;
}

// free() afterwards
unsigned char* image_getPixel(struct Image image, int x, int y) {
    unsigned char* pixelData = malloc(image.channels);

    for (int i = 0; i < image.channels; i++) {
        pixelData[i] = image.texture[image.channels * ((image.width * y) + x) + i];
    }

    return pixelData;
}

void image_printPixel(struct Image image, unsigned char* pixel) {
    switch (image.channels) {
        case 1:
            printf("\x1B[48;2;%i;0;0m  ", pixel[0]);
        case 2:
            printf("\x1B[48;2;%i;%i;0m  ", pixel[0], pixel[1]);
        default:
            printf("\x1B[48;2;%i;%i;%im  ", pixel[0], pixel[1], pixel[2]);
    }
}

int main() {
    struct Image img = image_new("img.png");

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char* pixel = image_getPixel(img, x, y);
            image_printPixel(img, pixel);
            free(pixel);
        }
        puts("\x1B[0m");
    }
}