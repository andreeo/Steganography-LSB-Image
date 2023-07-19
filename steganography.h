#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

struct ImageInfo *imageInfo;

void encode(char *inputFile, char *messageFile, char *outputFile);

void decode(char *inputFile, char *outputFile);

#endif