#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

//define structures
struct ImageInfo *imageInfo;

//define functions
void decode_image(char *inputFileName, struct ImageInfo *imageInfo);

void encode_image(char *outputFileName, struct ImageInfo *imageInfo);

void decimal2binary(int decimal, int *binary);

void binary2decimal(int *binary, int *decimal);

unsigned int getTotalChars(char *filename);

void char2binary(char *filename, int *binaries);

void LSBAlgorithm(struct ImageInfo decodedImageInfo, char *messageFile, struct ImageInfo *encodedImageInfo);

void encode(char *inputFile, char *messageFile, char *outputFile);

#endif