#ifndef GMM_H
#define GMM_H

#include <stdint.h>

// Optimized GMMEntry for multivariate data (e.g., multidimensional Gaussian components)
typedef struct {
    uint8_t num_components;     // 8-bit integer for the number of components
    uint16_t **quantized_means;  // 2D array for quantized multivariate means
    uint16_t **quantized_variances; // 2D array for quantized multivariate variances
    uint8_t *quantized_weights;  // 8-bit quantized weights
    int dimensions;              // Dimensions of multivariate data
} GMMEntryOptimized;

// Quantization and delta encoding functions
uint16_t* quantize_floats(float* values, int num_values, float min, float max, int bit_depth);
float* dequantize_floats(uint16_t* quantized_values, int num_values, float min, float max, int bit_depth);
void delta_encode(uint16_t* data, int num_values);
void delta_decode(uint16_t* data, int num_values);

// GMM database operations for optimized multivariate values
int insert_gmm_optimized(GMMEntryOptimized* gmm);
float gmm_probability_optimized(GMMEntryOptimized* gmm, float* values);
float* sample_from_gmm_optimized(GMMEntryOptimized* gmm);

// Functions for constructing and deconstructing GMMEntryOptimized
GMMEntryOptimized* create_gmm_entry(int num_components, int dimensions, float** means, float** variances, float* weights);
void free_gmm_entry(GMMEntryOptimized* gmm);

#endif // GMM_H