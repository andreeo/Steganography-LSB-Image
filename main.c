#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    // declare variables
    char
        *inputFile,
        *messageFile,
        *outputFile;

    // check if the arguments are valid
    if(argc == 1)
    {
        fprintf(stderr, "Invalid arguments\n");
        fprintf(stderr, "Usage: %s -e input-file.png message.txt staged-image.png \n", argv[0]);
        fprintf(stderr, "Usage: %s -d staged-image.png \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // assign arguments to variables
    if(strcmp(argv[1], "-e") == 0)
    {
        // check if the arguments are valid
        if(argc < 5)
        {
            fprintf(stderr, "Invalid arguments\n");
            fprintf(stderr, "Usage: %s -e input-file.png message.txt staged-image.png \n", argv[0]);
            exit(EXIT_FAILURE);
        }

        inputFile = argv[2];
        messageFile = argv[3];
        outputFile = argv[4];

        // here call encode function: encode(inputFile, messageFile, outputFile);
    }
    else if(strcmp(argv[1], "-d") == 0)
    {
        // check if the arguments are valid
        if(argc < 3)
        {
            fprintf(stderr, "Invalid arguments\n");
            fprintf(stderr, "Usage: %s -d staged-image.png \n", argv[0]);
            exit(EXIT_FAILURE);
        }

        inputFile = argv[2];

        // here call decode function: decode(inputFile);
    }
    else
    {
        fprintf(stderr, "Invalid arguments\n");
        fprintf(stderr, "Usage: %s -e input-file.png message.txt staged-image.png \n", argv[0]);
        fprintf(stderr, "Usage: %s -d staged-image.png \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}