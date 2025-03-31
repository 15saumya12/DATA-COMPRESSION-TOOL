#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress data using RLE
void rle_compress(char *data, char *compressed) {
    int i, count = 1;

    for (i = 1; i <= strlen(data); i++) {
        if (i == strlen(data) || data[i] != data[i - 1]) {
            sprintf(compressed, "%s%c%d", compressed, data[i - 1], count);
            count = 1;
        } else {
            count++;
        }
    }
}

// Function to decompress data using RLE
void rle_decompress(char *compressed, char *decompressed) {
    int i, count;
    char c;

    for (i = 0; i < strlen(compressed); i += 2) {
        c = compressed[i];
        count = compressed[i + 1] - '0';

        while (count-- > 0) {
            sprintf(decompressed, "%s%c", decompressed, c);
        }
    }
}

// Function to compress a file using RLE
void compress_file(char *input_file, char *output_file) {
    FILE *f_in, *f_out;
    char data[1024], compressed[2048];

    f_in = fopen(input_file, "r");
    if (f_in == NULL) {
        printf("Error opening input file\n");
        return;
    }

    f_out = fopen(output_file, "w");
    if (f_out == NULL) {
        printf("Error opening output file\n");
        fclose(f_in);
        return;
    }

    while (fgets(data, sizeof(data), f_in) != NULL) {
        rle_compress(data, compressed);
        fprintf(f_out, "%s", compressed);
    }

    fclose(f_in);
    fclose(f_out);
}

// Function to decompress a file using RLE
void decompress_file(char *input_file, char *output_file) {
    FILE *f_in, *f_out;
    char compressed[2048], decompressed[1024];

    f_in = fopen(input_file, "r");
    if (f_in == NULL) {
        printf("Error opening input file\n");
        return;
    }

    f_out = fopen(output_file, "w");
    if (f_out == NULL) {
        printf("Error opening output file\n");
        fclose(f_in);
        return;
    }

    while (fgets(compressed, sizeof(compressed), f_in) != NULL) {
        rle_decompress(compressed, decompressed);
        fprintf(f_out, "%s", decompressed);
    }

    fclose(f_in);
    fclose(f_out);
}

int main() {
    char input_file[100], output_file[100];
    int option;

    printf("RLE Compression Tool\n");
    printf("---------------------\n");

    while (1) {
        printf("Options:\n");
        printf("1. Compress a file\n");
        printf("2. Decompress a file\n");
        printf("3. Quit\n");

        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the input file path: ");
                scanf("%s", input_file);
                printf("Enter the output file path: ");
                scanf("%s", output_file);
                compress_file(input_file, output_file);
                printf("File compressed successfully!\n");
                break;
            case 2:
                printf("Enter the input file path: ");
                scanf("%s", input_file);
                printf("Enter the output file path: ");
                scanf("%s", output_file);
                decompress_file(input_file, output_file);
                printf("File decompressed successfully!\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid option. Please choose again.\n");
        }
    }

    return 0;
}
