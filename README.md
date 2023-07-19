# Image Steganography with LSB algorithm

Program in C based on steganography to hide data in PNG images using the LSB Algorithm.

## Compiling in C

```
$ gcc -Wall -o stega \
    main.c \
    steganography.c \
    steganography_util.c \
    3rdparty/lodepng/lodepng.c \
```

## Makefile

There is a Makefile, its execution is optional. Automates the build and cleanup process

### Building

```
$ make
```

or

```
$ make all
```

### Clean

```
$ make clean
```

## Usage

```
Usage: ./stega [required arguments]

Required arguments:
    -e      encode data with image
    -d      decode image and save data into a file
```

## Encoding
```
Usage: ./stega -e input-image.png message.txt output-image.png

Encode a data file into a image
```

## Decoding
```
Usage: ./stega -d input-image.png [-o output-text.txt]

Decode and extract data from an image

Optional arguments:
    -o specify the output file. [default: "message.txt"]
```

## Example

### Cover Image of 1300 x 731, 8-bit/color RGBA
![Cover Image](./input_image.png)

### Encoding

```
$ ./stega -e input_image.png secret_file.txt output_image.png
```

### Stego Image

![Stego Image](./output_image.png)

### Decoding
```
$ ./stega -d output_image.png
```

Now open the generated text file to see the extracted data

### License

MIT
