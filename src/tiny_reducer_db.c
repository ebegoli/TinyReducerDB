#include <stdio.h>
#include <stdlib.h>
#include "gmm.h"

#define DB_PATH "data/tiny_data.bin"

// Save GMM parameters to binary file.
void save_gmm_to_db(const GMM *model) {
    FILE *file = fopen(DB_PATH, "wb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fwrite(model, sizeof(GMM), 1, file);
    fclose(file);
    printf("GMM model saved to %s\n", DB_PATH);
}

// Load GMM parameters from binary file.
void load_gmm_from_db(GMM *model) {
    FILE *file = fopen(DB_PATH, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fread(model, sizeof(GMM), 1, file);
    fclose(file);
    printf("GMM model loaded from %s\n", DB_PATH);
}
