#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    // declare variables
    int opt;
    char* inputFile, *messageFile, *outputFile;

    // check if the number of arguments is correct
    if(argc  < 7 || argc == 8)
    {
        fprintf(stderr, "Usage: %s [-i input-file] [-mf message file] [-o output file]\n",
                    argv[0]);
        exit(EXIT_FAILURE);
    }

    // parse the arguments
    while ((opt = getopt(argc, argv, "imfo")) != -1) {
        printf("%d\n", opt);
        switch (opt) {
        case 'i':
            inputFile  = argv[optind];
            break;
        case 'm':
            messageFile = argv[optind];
            break;
        case 'o':
            outputFile = argv[optind];
            break;
        default: // 
            fprintf(stderr, "Usage: %s [-i input-file] [-m message file] [-o output-file]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}