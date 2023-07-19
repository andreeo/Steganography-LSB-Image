#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "steganography_util.h"
#include "steganography_common.h"

/*
*   Function: encode
*   ----------------------
*   Encodes the image with the message
*
*   Parameters:
*       inputFile: the name of the input file
*       messageFile: the name of the message file
*       outputFile: the name of the output file
*
*   returns: void
*/
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

/*
*   Function: decode
*   ----------------------
*   Decodes the image and stores the message in the output file
*
*   Parameters:
*       inputFile: the name of the input file
*       outputFile: the name of the output file
*
*   returns: void
*/
void decode(char *inputFile, char *outputFile)
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

    FILE *file = fopen(outputFile, "w");
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