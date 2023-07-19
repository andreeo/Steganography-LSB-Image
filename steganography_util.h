#ifndef STEGANOGRAPHY_UTIL_H
#define STEGANOGRAPHY_UTIL_H
#include "steganography_common.h"

void decode_image(char *inputFileName, struct ImageInfo *imageInfo);

void encode_image(char *outputFileName, struct ImageInfo *imageInfo);

void decimal2binary(int decimal, int *binary);

void binary2decimal(int *binary, int *decimal);

void reverse(int  *binary, int *reversedBinary);

unsigned int getTotalChars(char *filename);

void char2binary(char *filename, int *binaries);

void LSBAlgorithm(struct ImageInfo decodedImageInfo, char *messageFile, struct ImageInfo *encodedImageInfo);

#endif