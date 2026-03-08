#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>    // errno

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        return 1;
    }

    const char *inname = argv[1];
    const char *outname = argv[2];

    if (strcmp(inname, outname) == 0) {
        fprintf(stderr, "Error: input and output file names must be different.\n");
        return 1;
    }

    FILE *in = fopen(inname, "rb");
    if (!in) {
        perror("fopen input");
        return 1;
    }

    FILE *out = fopen(outname, "wb");
    if (!out) {
        perror("fopen output");
        fclose(in);
        return 1;
    }

    unsigned char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            perror("write error");
            fclose(in);
            fclose(out);
            return 1;
        }
    }

    if (ferror(in)) {
        perror("read error");
        fclose(in);
        fclose(out);
        return 1;
    }

    if (fclose(in) == EOF) {
        perror("fclose input");
        fclose(out);
        return 1;
    }

    if (fclose(out) == EOF) {
        perror("fclose output");
        return 1;
    }

    printf("Copy complete: '%s' -> '%s'\n", inname, outname);
    return 0;
}