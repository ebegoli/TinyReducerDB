#include <stdio.h>
#include <assert.h>
#include "GMM.h"

void test_quantization() {
    // Sample values for quantization testing
    float values[5] = {0.1, 0.3, 0.5, 0.7, 0.9};
    float min_value = 0.0;
    float max_value = 1.0;

    // Quantize and dequantize the values
    uint16_t* quantized_values = quantize_floats(values, 5, min_value, max_value, 16);
    float* dequantized_values = dequantize_floats(quantized_values, 5, min_value, max_value, 16);

    // Test that the dequantized values are approximately the same as the original ones
    for (int i = 0; i < 5; i++) {
        assert(fabs(values[i] - dequantized_values[i]) < 0.01 && "Quantization/dequantization mismatch");
    }

    printf("Quantization tests passed!\n");

    // Cleanup
    free(quantized_values);
    free(dequantized_values);
}

int main() {
    test_quantization();
    return 0;
}