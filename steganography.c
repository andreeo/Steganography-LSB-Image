#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "3rdparty/lodepng/lodepng.h"

#define BYTE 8

struct ImageInfo
{           
    /* data */
    unsigned char *image;
    unsigned int width;
    unsigned int height;
};

// declare function to decode image
void decode_image(char *inputFileName, struct ImageInfo *imageInfo)
{
    unsigned error;
    unsigned char *image = 0;
    unsigned width, height;

    // decode
    error = lodepng_decode32_file(&image, &width, &height, inputFileName);

    // if there's an error, display it
    if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

    // store the image info
    imageInfo->image = 0;
    imageInfo->image = image;
    imageInfo->width = width;
    imageInfo->height = height;

    //free(image); // free memory used by image

    return;
}

// declare function to encode image
void encode_image(char *outputFileName, struct ImageInfo *imageInfo)
{
    unsigned error;

    // encode
    error = lodepng_encode32_file(outputFileName, imageInfo->image, imageInfo->width, imageInfo->height);

    // if there's an error, display it
    if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}


void decimal2binary(int decimal, int *binary)
{
    int i = 0;
    while(decimal > 0)
    {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }

    if(i < BYTE)
    {
        for(int j = i; j < BYTE; j++)
        {
            binary[j] = 0;
        }
    }
}

void binary2decimal(int *binary, int *decimal)
{
    int i = 0;
    while(i < BYTE)
    {
        *decimal += binary[i] * (1 << i);
        i++;
    }
}

void reverse(int *binary, int *reversedBinary)
{
    int j = 7;
    for(int i = 0; i < BYTE; i++)
    {
        reversedBinary[j] = binary[i];
        j--;
    }
}

unsigned int getTotalChars(char *filename)
{
    // read file
    FILE *file = fopen(filename, "r");
    
    // read character by character
    char c;
    unsigned int j = 0;
    while((c = fgetc(file)) != EOF)
    {
        j++;
    }
    fclose(file);

    return j;
}

void char2binary(char *filename, int *binaries)
{
    char c;
    int k = 0, *bin = malloc(sizeof(int) * BYTE);

    FILE *file = fopen(filename, "r");

    while((c = fgetc(file)) != EOF)
    {
        for(int i = 0; i < BYTE; i++)
        {
            bin[i] = ((c << i) & 0x80) ? 1 : 0;
            binaries[k] = bin[i];
            k++;
        }
    }
    fclose(file);
}

void LSBAlgorithm(struct ImageInfo decodedImageInfo, char *messageFile, struct ImageInfo *encodedImageInfo)
{

    int
        j = getTotalChars(messageFile),
        totalBits = BYTE * j,
        *binaries = malloc(sizeof(int)*totalBits),
        count = 0;

    size_t imageSize = decodedImageInfo.width * decodedImageInfo.height * 4;

    char2binary(messageFile, binaries);

    //modify each byte of the image
    for(int i = 0; i < imageSize; i++)
    {
        // allocate memory for binary number
        int *binary = malloc(sizeof(int) * BYTE);

        // convert decimal to binary
        decimal2binary(decodedImageInfo.image[i], binary);
        
        if(i < totalBits)
        {
            binary[0] = binaries[i];
        }
        else if(count < BYTE)
        {
            binary[0] = 0;
            count++;
        } 

        // allocate  memory for decimal number
        int *decimal = malloc(sizeof(int));
        *decimal = 0;

        // convert binary to decimal
        binary2decimal(binary, decimal);

        // modify the image
        encodedImageInfo->image[i] = *decimal;

        // free memory
        free(decimal);
        free(binary);
    }

}

void encode(char *inputFile, char *messageFile, char *outputFile)
{
    struct ImageInfo decodedImageInfo, encodedImageInfo;

    //  decode image
    decode_image(inputFile, &decodedImageInfo);

    // copy decoded image info to encoded image info
    memcpy(&encodedImageInfo, &decodedImageInfo, sizeof(decodedImageInfo));

    // apply LSB algorithm to encode image
    LSBAlgorithm(decodedImageInfo, messageFile, &encodedImageInfo);

    // encode image
    encode_image(outputFile, &encodedImageInfo);
}

void decode(char *inputFile)
{
    struct ImageInfo decodedImageInfo;

    decode_image(inputFile, &decodedImageInfo);

    size_t imageSize = decodedImageInfo.width * decodedImageInfo.height * 4;

    // allocate memory for binary number
    int
        *binary = malloc(sizeof(int) * BYTE),
        *binBuffer = malloc(sizeof(int) * BYTE),
        *decimal = malloc(sizeof(int)),
        *reversedBinary = malloc(sizeof(int) * BYTE),
        count = 0;

    FILE *file = fopen("message.txt", "w");
    if(file == NULL)
    {
        printf("Error opening file!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < imageSize; i++)
    {

        // convert decimal to binary
        decimal2binary(decodedImageInfo.image[i], binary);


        if(count < BYTE)
        {
            binBuffer[count] = binary[0];
            if(count == 7)
            {
                *decimal = 0;
                reverse(binBuffer, reversedBinary);
                binary2decimal(reversedBinary, decimal);
                
                if(*decimal != 0)
                {
                    fprintf(file, "%c", *decimal);
                }
                else
                {
                    exit(EXIT_SUCCESS);
                }

            }

            count++;
        }

        if(count == BYTE) count = 0;
    }

    fclose(file);
}