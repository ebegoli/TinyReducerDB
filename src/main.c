#include <stdio.h>
#include <stdlib.h>
#include "gmm.h"

int main() {
    // Example GMM for a 2D multivariate distribution with 3 components
    float means[3][2] = {{0.2, 0.3}, {0.5, 0.5}, {0.8, 0.7}};
    float variances[3][2] = {{0.05, 0.04}, {0.03, 0.02}, {0.06, 0.05}};
    float weights[3] = {0.3, 0.5, 0.2};

    float* means_ptrs[3] = {means[0], means[1], means[2]};
    float* variances_ptrs[3] = {variances[0], variances[1], variances[2]};

    GMMEntry* gmm = create_gmm_entry(3, 2, means_ptrs, variances_ptrs, weights);

    // Insert the GMM entry
    int id = insert_gmm_optimized(gmm);
    printf("Inserted GMM with ID: %d\n", id);

    // Query a probability
    float input[2] = {0.4, 0.5};
    float prob = gmm_probability_optimized(gmm, input);
    printf("Probability of input: %f\n", prob);

    // Sample from GMM
    float* sample = sample_from_gmm_optimized(gmm);
    printf("Sampled values: %f, %f\n", sample[0], sample[1]);

    // Clean up
    free(sample);
    free_gmm_entry(gmm);

    return 0;
}
