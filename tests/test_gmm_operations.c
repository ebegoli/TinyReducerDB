#include <stdio.h>
#include <assert.h>
#include "gmm.h"

void test_gmm_insertion() {
    // Example GMM for a 2D multivariate distribution
    float means[3][2] = {{0.2, 0.3}, {0.5, 0.5}, {0.8, 0.7}};
    float variances[3][2] = {{0.05, 0.04}, {0.03, 0.02}, {0.06, 0.05}};
    float weights[3] = {0.3, 0.5, 0.2};

    float* means_ptrs[3] = {means[0], means[1], means[2]};
    float* variances_ptrs[3] = {variances[0], variances[1], variances[2]};

    GMMEntry* gmm = create_gmm_entry(3, 2, means_ptrs, variances_ptrs, weights);

    // Insert GMM and test that it gets an ID
    int id = insert_gmm_optimized(gmm);
    assert(id >= 0 && "Failed to insert GMM");

    printf("GMM insertion test passed with ID: %d\n", id);

    // Clean up
    free_gmm_entry(gmm);
}

void test_gmm_query() {
    // Same GMM setup as above
    float means[3][2] = {{0.2, 0.3}, {0.5, 0.5}, {0.8, 0.7}};
    float variances[3][2] = {{0.05, 0.04}, {0.03, 0.02}, {0.06, 0.05}};
    float weights[3] = {0.3, 0.5, 0.2};

    float* means_ptrs[3] = {means[0], means[1], means[2]};
    float* variances_ptrs[3] = {variances[0], variances[1], variances[2]};

    GMMEntry* gmm = create_gmm_entry(3, 2, means_ptrs, variances_ptrs, weights);

    // Query a probability
    float input[2] = {0.4, 0.5};
    float prob = gmm_probability_optimized(gmm, input);
    assert(prob >= 0 && prob <= 1 && "GMM query returned invalid probability");

    printf("GMM query test passed with probability: %f\n", prob);

    // Clean up
    free_gmm_entry(gmm);
}

void test_gmm_sampling() {
    // Same GMM setup as above
    float means[3][2] = {{0.2, 0.3}, {0.5, 0.5}, {0.8, 0.7}};
    float variances[3][2] = {{0.05, 0.04}, {0.03, 0.02}, {0.06, 0.05}};
    float weights[3] = {0.3, 0.5, 0.2};

    float* means_ptrs[3] = {means[0], means[1], means[2]};
    float* variances_ptrs[3] = {variances[0], variances[1], variances[2]};

    GMMEntry* gmm = create_gmm_entry(3, 2, means_ptrs, variances_ptrs, weights);

    // Sample from GMM
    float* sample = sample_from_gmm_optimized(gmm);
    assert(sample != NULL && "GMM sampling failed");

    printf("GMM sampling test passed with sample: %f, %f\n", sample[0], sample[1]);

    // Clean up
    free(sample);
    free_gmm_entry(gmm);
}

int main() {
    test_gmm_insertion();
    test_gmm_query();
    test_gmm_sampling();
    return 0;
}
