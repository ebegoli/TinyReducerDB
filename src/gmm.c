#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gmm.h"

#define THRESHOLD 1e-6  // Convergence threshold

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

// Gaussian PDF for a 2D point
static double gaussian_pdf(double x[2], double mean[2], double cov[2][2]) {
    double det = cov[0][0] * cov[1][1] - cov[0][1] * cov[1][0];
    double inv_cov[2][2] = {
        { cov[1][1] / det, -cov[0][1] / det },
        { -cov[1][0] / det, cov[0][0] / det }
    };

    double diff[2] = { x[0] - mean[0], x[1] - mean[1] };
    double mahalanobis = diff[0] * (inv_cov[0][0] * diff[0] + inv_cov[0][1] * diff[1]) +
                         diff[1] * (inv_cov[1][0] * diff[0] + inv_cov[1][1] * diff[1]);

    double norm_factor = 1.0 / (2 * M_PI * sqrt(det));
    return norm_factor * exp(-0.5 * mahalanobis);
}

// Initialize GMM parameters randomly
static void init_gmm(GMM *model, int k) {
    model->num_clusters = k;
    for (int i = 0; i < k; ++i) {
        model->means[i][0] = rand() % 10;
        model->means[i][1] = rand() % 10;
        model->weights[i] = 1.0 / k;
        model->covariances[i][0][0] = 1.0;
        model->covariances[i][1][1] = 1.0;
        model->covariances[i][0][1] = model->covariances[i][1][0] = 0.0;
        model->cluster_counts[i] = 0;
    }
}


/** Support for incremental updates:
When a new data point arrives, run responsibilities (E-step): Compute the responsibilities of the new point for each cluster.
run an m-step (Incremental Update): Update the parameters (means, covariances, and weights) using running estimates.
*/

// E-step: Compute the responsibilities for a new data point
static void compute_responsibilities(const GMM *model, double new_point[2], double *responsibilities) {
    double sum = 0.0;
    for (int j = 0; j < model->num_clusters; ++j) {
        responsibilities[j] = model->weights[j] * gaussian_pdf(new_point, model->means[j], model->covariances[j]);
        sum += responsibilities[j];
    }
    // Normalize responsibilities
    for (int j = 0; j < model->num_clusters; ++j) {
        responsibilities[j] /= sum;
    }
}

// Incrementally update the GMM parameters
void update_gmm(GMM *model, double new_point[2]) {
    double responsibilities[MAX_CLUSTERS];
    compute_responsibilities(model, new_point, responsibilities);

    // Update parameters for each cluster
    for (int j = 0; j < model->num_clusters; ++j) {
        double r = responsibilities[j];
        model->cluster_counts[j] += 1;
        double n_j = model->cluster_counts[j];

        // Incremental mean update using Welford’s method
        double old_mean[2] = { model->means[j][0], model->means[j][1] };
        model->means[j][0] += (r / n_j) * (new_point[0] - old_mean[0]);
        model->means[j][1] += (r / n_j) * (new_point[1] - old_mean[1]);

        // Incremental covariance update
        double diff[2] = { new_point[0] - model->means[j][0], new_point[1] - model->means[j][1] };
        model->covariances[j][0][0] += r * (diff[0] * diff[0] - model->covariances[j][0][0]) / n_j;
        model->covariances[j][0][1] += r * (diff[0] * diff[1] - model->covariances[j][0][1]) / n_j;
        model->covariances[j][1][0] = model->covariances[j][0][1];
        model->covariances[j][1][1] += r * (diff[1] * diff[1] - model->covariances[j][1][1]) / n_j;

        // Update the weights
        model->weights[j] = (double)model->cluster_counts[j] / (double)(n_j);
    }
}

// Print GMM parameters to the console
void print_gmm(const GMM *model) {
    printf("GMM Model with %d clusters:\n", model->num_clusters);
    for (int i = 0; i < model->num_clusters; ++i) {
        printf("Cluster %d: Mean = (%f, %f), Weight = %f\n", 
               i, model->means[i][0], model->means[i][1], model->weights[i]);
    }
}
