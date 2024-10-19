#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "gmm.h"

#define MAX_ITER 100  // Maximum number of EM iterations
#define THRESHOLD 1e-6  // Convergence threshold

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
    }
}

// E-step: Compute responsibilities (posterior probabilities)
static void e_step(const GMM *model, double data[][2], int n, double responsibilities[][MAX_CLUSTERS]) {
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < model->num_clusters; ++j) {
            responsibilities[i][j] = model->weights[j] * gaussian_pdf(data[i], model->means[j], model->covariances[j]);
            sum += responsibilities[i][j];
        }
        // Normalize responsibilities for each data point
        for (int j = 0; j < model->num_clusters; ++j) {
            responsibilities[i][j] /= sum;
        }
    }
}

// M-step: Update the GMM parameters
static void m_step(GMM *model, double data[][2], int n, double responsibilities[][MAX_CLUSTERS]) {
    int k = model->num_clusters;

    for (int j = 0; j < k; ++j) {
        double sum_resp = 0.0;
        double mean[2] = {0.0, 0.0};
        double cov[2][2] = { {0.0, 0.0}, {0.0, 0.0} };

        // Compute mean and weighted covariance
        for (int i = 0; i < n; ++i) {
            double r = responsibilities[i][j];
            sum_resp += r;

            mean[0] += r * data[i][0];
            mean[1] += r * data[i][1];
        }
        mean[0] /= sum_resp;
        mean[1] /= sum_resp;

        for (int i = 0; i < n; ++i) {
            double r = responsibilities[i][j];
            double diff[2] = { data[i][0] - mean[0], data[i][1] - mean[1] };
            cov[0][0] += r * diff[0] * diff[0];
            cov[0][1] += r * diff[0] * diff[1];
            cov[1][0] += r * diff[1] * diff[0];
            cov[1][1] += r * diff[1] * diff[1];
        }
        cov[0][0] /= sum_resp;
        cov[0][1] /= sum_resp;
        cov[1][0] /= sum_resp;
        cov[1][1] /= sum_resp;

        // Update parameters
        model->means[j][0] = mean[0];
        model->means[j][1] = mean[1];
        model->covariances[j][0][0] = cov[0][0];
        model->covariances[j][0][1] = cov[0][1];
        model->covariances[j][1][0] = cov[1][0];
        model->covariances[j][1][1] = cov[1][1];
        model->weights[j] = sum_resp / n;
    }
}

// Compute log-likelihood of the data given the model
static double compute_log_likelihood(const GMM *model, double data[][2], int n) {
    double log_likelihood = 0.0;
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < model->num_clusters; ++j) {
            sum += model->weights[j] * gaussian_pdf(data[i], model->means[j], model->covariances[j]);
        }
        log_likelihood += log(sum);
    }
    return log_likelihood;
}

// Fit GMM using the EM algorithm
void fit_gmm(GMM *model, double data[][2], int n, int k) {
    init_gmm(model, k);

    double responsibilities[n][MAX_CLUSTERS];
    double prev_log_likelihood = -DBL_MAX;

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        e_step(model, data, n, responsibilities);
        m_step(model, data, n, responsibilities);

        double log_likelihood = compute_log_likelihood(model, data, n);
        printf("Iteration %d: Log-Likelihood = %f\n", iter + 1, log_likelihood);

        if (fabs(log_likelihood - prev_log_likelihood) < THRESHOLD) {
            printf("Converged after %d iterations.\n", iter + 1);
            break;
        }
        prev_log_likelihood = log_likelihood;
    }
}
