#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmm.h"

// Initialize random GMM parameters (for simplicity).
static void init_gmm(GMM *model, int k) {
    model->num_clusters = k;
    for (int i = 0; i < k; ++i) {
        model->means[i][0] = rand() % 10;
        model->means[i][1] = rand() % 10;
        model->weights[i] = 1.0 / k;
        model->covariances[i][0][0] = 1.0;
        model->covariances[i][1][1] = 1.0;
    }
}

// Simple EM-like fitting function (stubbed).
void fit_gmm(GMM *model, double data[][2], int n, int k) {
    init_gmm(model, k);  // Initialize parameters
    printf("Fitted GMM with %d clusters.\n", k);
}

// Print GMM parameters to the console.
void print_gmm(const GMM *model) {
    printf("GMM Model with %d clusters:\n", model->num_clusters);
    for (int i = 0; i < model->num_clusters; ++i) {
        printf("Cluster %d: Mean = (%f, %f), Weight = %f\n", 
               i, model->means[i][0], model->means[i][1], model->weights[i]);
    }
}
