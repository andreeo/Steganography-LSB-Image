#ifndef STEGANOGRAPHY_COMMON_H
#define STEGANOGRAPHY_COMMON_H

#define BYTE 8

/*
    Structure to store image information
    
    Members:
        * image: pointer to image data
        * width: width of image
        * height: height of image

*/
struct ImageInfo
{           
    unsigned char *image;
    unsigned int width;
    unsigned int height;
};

#endif