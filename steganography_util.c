#include <stdlib.h>
#include <stdio.h>
#include "3rdparty/lodepng/lodepng.h"
#include "steganography_common.h"


/*
*   Function: decode_image
*   ----------------------
*   Decodes the image and stores the image info in the struct
*
*   Parameters:
*       inputFileName: the name of the input file
*       imageInfo: the struct to store the image info
*
*   returns: void
*/
void
decode_image (char *inputFileName, struct ImageInfo *imageInfo)
{
  unsigned error;
  unsigned char *image = 0;
  unsigned width, height;

  // decode
  error = lodepng_decode32_file (&image, &width, &height, inputFileName);

  // if there's an error, display it
  if (error)
    printf ("error %u: %s\n", error, lodepng_error_text (error));

  // store the image info
  imageInfo->image = 0;
  imageInfo->image = image;
  imageInfo->width = width;
  imageInfo->height = height;

  //free(image); // free memory used by image

  return;
}

/*
*   Function: encode_image
*   ----------------------
*   Encodes the image and stores the image info in the struct
*
*   Parameters:
*       outputFileName: the name of the output file
*       imageInfo: the struct to store the image info
*
*   returns: void
*/
void
encode_image (char *outputFileName, struct ImageInfo *imageInfo)
{
  unsigned error;

  // encode
  error =
    lodepng_encode32_file (outputFileName, imageInfo->image, imageInfo->width,
                           imageInfo->height);

  // if there's an error, display it
  if (error)
    printf ("error %u: %s\n", error, lodepng_error_text (error));
}

/*
*   Function: decimal2binary
*   ------------------------
*   Converts a decimal number to a binary number
*
*   Parameters:
*       decimal: the decimal number to be converted
*       binary: the binary number to store the result
*
*   returns: void
*/
void
decimal2binary (int decimal, int *binary)
{
  int i = 0;
  while (decimal > 0)
  {
    binary[i] = decimal % 2;
    decimal = decimal / 2;
    i++;
  }

  if (i < BYTE)
  {
    for (int j = i; j < BYTE; j++)
    {
      binary[j] = 0;
    }
  }
}

/*
*   Function: binary2decimal
*   ------------------------
*   Converts a binary number to a decimal number
*
*   Parameters:
*       binary: the binary number to be converted
*       decimal: the decimal number to store the result
*
*   returns: void
*/
void
binary2decimal (int *binary, int *decimal)
{
  int i = 0;
  while (i < BYTE)
  {
    // shift left by i bits and add to decimal
    *decimal += binary[i] * (1 << i);
    i++;
  }
}

/*
*   Function: reverse
*   -----------------
*   Reverses the binary number
*
*   Parameters:
*       binary: the binary number to be reversed
*       reversedBinary: the reversed binary number to store the result
*
*   returns: void
*/
void
reverse (int *binary, int *reversedBinary)
{
  int j = 7;
  for (int i = 0; i < BYTE; i++)
  {
    reversedBinary[j] = binary[i];
    j--;
  }
}

/*
*   Function: getTotalChars
*   -----------------------
*   Gets the total number of characters in a file
*
*   Parameters:
*       filename: the name of the file
*
*   returns: int - the total number of characters in a file
*/
unsigned int
getTotalChars (char *filename)
{
  // read file
  FILE *file = fopen (filename, "r");

  // read character by character
  char c;
  unsigned int j = 0;
  while ((c = fgetc (file)) != EOF)
  {
    j++;
  }
  fclose (file);

  return j;
}

/*
*   Function: char2binary
*   ---------------------
*   Converts a character to a binary number
*
*   Parameters:
*       filename: the name of the file
*       binaries: the binary number to store the result
*
*   returns: void
*/
void
char2binary (char *filename, int *binaries)
{
  char c;
  int k = 0, *bin = malloc (sizeof (int) * BYTE);

  FILE *file = fopen (filename, "r");

  while ((c = fgetc (file)) != EOF)
  {
    for (int i = 0; i < BYTE; i++)
    {
      bin[i] = ((c << i) & 0x80) ? 1 : 0;
      binaries[k] = bin[i];
      k++;
    }
  }
  fclose (file);
}

/*
*   Function: LSBAlgorithm
*   ----------------------
*   Implements the LSB algorithm
*
*   Parameters:
*       decodedImageInfo: the struct that contains the decoded image info
*       messageFile: the name of the file that contains the message
*       encodedImageInfo: the struct that contains the encoded image info
*
*   returns: void
*/
void
LSBAlgorithm (struct ImageInfo decodedImageInfo, char *messageFile,
              struct ImageInfo *encodedImageInfo)
{

  int
    j = getTotalChars (messageFile),
    totalBits = BYTE * j,
    *binaries = malloc (sizeof (int) * totalBits), count = 0;

  size_t imageSize = decodedImageInfo.width * decodedImageInfo.height * 4;

  char2binary (messageFile, binaries);

  //modify each byte of the image
  for (int i = 0; i < imageSize; i++)
  {
    // allocate memory for binary number
    int *binary = malloc (sizeof (int) * BYTE);

    // convert decimal to binary
    decimal2binary (decodedImageInfo.image[i], binary);

    if (i < totalBits)
    {
      binary[0] = binaries[i];
    }
    else if (count < BYTE)
    {
      binary[0] = 0;
      count++;
    }

    // allocate  memory for decimal number
    int *decimal = malloc (sizeof (int));
    *decimal = 0;

    // convert binary to decimal
    binary2decimal (binary, decimal);

    // modify the image
    encodedImageInfo->image[i] = *decimal;

    // free memory
    free (decimal);
    free (binary);
  }

}
