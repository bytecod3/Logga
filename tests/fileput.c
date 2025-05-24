/**
 * This program copies the contents of one input file to
 * the output file
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define USE_FREAD 0
#define MAX_BUFFER_SIZE 100

int main() {
    // create input and output file pointers
    FILE* fin;
    FILE* fout;

    char in_file[30]  = "input.txt";
    char out_file[30]  = "output.txt";
    int c;
    int n; // number of bytes read

    char read_buffer[MAX_BUFFER_SIZE];

#if USE_FREAD
    if((fin = fopen(in_file, "r")) == NULL) {
        printf("Could not open file. Please check\n");
        exit(EXIT_FAILURE);
    } else if ((fout = fopen(out_file, "w")) == NULL) {
        printf("Could not open file. Please check\n");
        exit(EXIT_FAILURE);
    } else {
        while((c = fread(read_buffer, 1, MAX_BUFFER_SIZE, fin)) != EOF) {
            fwrite(read_buffer, 1, MAX_BUFFER_SIZE, fout);
        }

    }

#else
    if((fin = fopen(in_file, "r")) == NULL) {
        printf("Could not open file. Please check\n");
        exit(EXIT_FAILURE);

    } else if ((fout = fopen(out_file, "w")) == NULL) {
        printf("Could not open file. Please check\n");
        exit(EXIT_FAILURE);

    } else {
        while ((c = getc(fin)) != EOF) {
            putc(c, fout);
            ++n;
        }

        if(feof(fin)) {
            puts("End of file reached");
            printf("Total number of bytes read: %d\n", n);
        }

        printf("Destination file has been copied");
    }
#endif

    return EXIT_SUCCESS;
}