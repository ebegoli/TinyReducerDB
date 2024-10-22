#include "gmm.h"
#include <stdlib.h>
#include <math.h>

// Quantize the floating-point numbers
uint16_t* quantize_floats(float* values, int num_values, float min_value, float max_value, int bit_depth) {
    uint16_t* quantized_values = (uint16_t*) malloc(num_values * sizeof(uint16_t));
    uint16_t max_quant = (1 << bit_depth) - 1;
    for (int i = 0; i < num_values; i++) {
        quantized_values[i] = (uint16_t)((values[i] - min_value) * max_quant / (max_value - min_value));
    }
    return quantized_values;
}

// Dequantization to restore floating-point numbers
float* dequantize_floats(uint16_t* quantized_values, int num_values, float min_value, float max_value, int bit_depth) {
    float* dequantized_values = (float*) malloc(num_values * sizeof(float));
    uint16_t max_quant = (1 << bit_depth) - 1;
    for (int i = 0; i < num_values; i++) {
        dequantized_values[i] = ((float)quantized_values[i] / max_quant) * (max_value - min_value) + min_value;
    }
    return dequantized_values;
}

// Encoding delta -- differential between the distributional values
void delta_encode(uint16_t* data, int num_values) {
    for (int i = num_values - 1; i > 0; i--) {
        data[i] -= data[i - 1];
    }
}

// Decode the delta of the representation
void delta_decode(uint16_t* data, int num_values) {
    for (int i = 1; i < num_values; i++) {
        data[i] += data[i - 1];
    }
}

// Construct a GMMEntry with quantization and delta encoding
GMMEntry* create_gmm_entry(int num_components, int dimensions, float** means, float** variances, float* weights) {
    GMMEntry* gmm = (GMMEntry*) malloc(sizeof(GMMEntry));
    gmm->num_components = num_components;
    gmm->dimensions = dimensions;

    gmm->means = (uint16_t**) malloc(num_components * sizeof(uint16_t*));
    gmm->variances = (uint16_t**) malloc(num_components * sizeof(uint16_t*));
    for (int i = 0; i < num_components; i++) {
        gmm->means[i] = quantize_floats(means[i], dimensions, 0, 1, 16);
        gmm->variances[i] = quantize_floats(variances[i], dimensions, 0, 1, 16);
        delta_encode(gmm->means[i], dimensions);
        delta_encode(gmm->variances[i], dimensions);
    }

    gmm->weights = quantize_floats(weights, num_components, 0, 1, 8);

    return gmm;
}

// Free the GMMEntryOptimized struct
void free_gmm_entry(GMMEntry* gmm) {
    for (int i = 0; i < gmm->num_components; i++) {
        free(gmm->means[i]);
        free(gmm->variances[i]);
    }
    free(gmm->means);
    free(gmm->variances);
    free(gmm->weights);
    free(gmm);
}

// Insert the optimized GMM entry
int insert_gmm_optimized(GMMEntry* gmm) {
    // Mock insert logic
    return rand() % 1000;
}

// Calculate the probability for a given multivariate input
float gmm_probability_optimized(GMMEntry* gmm, float* values) {
    // Mock probability computation
    return 0.5f;
}

// Sample from the GMM (mock logic)
float* sample_from_gmm_optimized(GMMEntry* gmm) {
    float* sample = (float*) malloc(gmm->dimensions * sizeof(float));
    for (int i = 0; i < gmm->dimensions; i++) {
        sample[i] = 0.5f;  // Mock value
    }
    return sample;
}
