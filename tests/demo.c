#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GMM.h"

// Function declarations
GMMEntry* create_network_gmm();
float* generate_network_sample(GMMEntry* gmm);
void free_gmm_entry(GMMEntry* gmm);

// Helper function to generate random values from normal distribution
float normal_random(float mean, float std_dev) {
    float u = ((float)rand() / RAND_MAX) * 2 - 1;
    float v = ((float)rand() / RAND_MAX) * 2 - 1;
    float r = u * u + v * v;
    if (r == 0 || r >= 1) return normal_random(mean, std_dev);
    float c = sqrt(-2 * log(r) / r);
    return mean + u * c * std_dev;
}

// Generate a random sample from the GMM
float* generate_network_sample(GMMEntry* gmm) {
    // Randomly select a GMM component based on the weights
    float rand_weight = (float)rand() / RAND_MAX;
    float cumulative_weight = 0.0;
    int component = -1;
    for (int i = 0; i < gmm->num_components; i++) {
        cumulative_weight += gmm->weights[i];
        if (rand_weight <= cumulative_weight) {
            component = i;
            break;
        }
    }

    // Generate sample from the chosen component
    float* sample = malloc(gmm->dimension * sizeof(float));
    for (int d = 0; d < gmm->dimension; d++) {
        sample[d] = normal_random(gmm->means[component][d], sqrt(gmm->variances[component][d]));
    }
    return sample;
}

// Simulate network traffic data with a mixture of different GMM components
GMMEntry* create_network_gmm() {
    int num_components = 3;
    int dimension = 3; // Packet size, inter-arrival time, bandwidth

    // Allocate memory for GMMEntryOptimized
    GMMEntry* gmm = malloc(sizeof(GMMEntry));
    gmm->num_components = num_components;
    gmm->dimension = dimension;
    
    gmm->means = malloc(num_components * sizeof(float*));
    gmm->variances = malloc(num_components * sizeof(float*));
    gmm->weights = malloc(num_components * sizeof(float));

    for (int i = 0; i < num_components; i++) {
        gmm->means[i] = malloc(dimension * sizeof(float));
        gmm->variances[i] = malloc(dimension * sizeof(float));
    }

    // Define network traffic patterns for different scenarios
    // Component 1: Normal traffic
    gmm->means[0][0] = 500.0;  // Average packet size (bytes)
    gmm->means[0][1] = 100.0;  // Average inter-arrival time (ms)
    gmm->means[0][2] = 1000.0; // Average bandwidth (kbps)
    gmm->variances[0][0] = 50.0;
    gmm->variances[0][1] = 10.0;
    gmm->variances[0][2] = 200.0;
    gmm->weights[0] = 0.6; // 60% of the data is normal traffic

    // Component 2: High-load traffic
    gmm->means[1][0] = 800.0;  // Larger packet size
    gmm->means[1][1] = 50.0;   // Shorter inter-arrival time
    gmm->means[1][2] = 2000.0; // Higher bandwidth usage
    gmm->variances[1][0] = 80.0;
    gmm->variances[1][1] = 20.0;
    gmm->variances[1][2] = 400.0;
    gmm->weights[1] = 0.3; // 30% of the data is high-load traffic

    // Component 3: Anomalous traffic
    gmm->means[2][0] = 1500.0; // Much larger packet size
    gmm->means[2][1] = 200.0;  // Longer inter-arrival time
    gmm->means[2][2] = 500.0;  // Lower bandwidth usage (e.g., network congestion)
    gmm->variances[2][0] = 100.0;
    gmm->variances[2][1] = 50.0;
    gmm->variances[2][2] = 100.0;
    gmm->weights[2] = 0.1; // 10% of the data is anomalous traffic

    return gmm;
}

// Free the GMM entry memory
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
