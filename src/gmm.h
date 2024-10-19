#ifndef GMM_H
#define GMM_H

#define MAX_CLUSTERS 5  // Max number of GMM clusters

typedef struct {
    double means[MAX_CLUSTERS][2];      // Mean vectors (2D example)
    double covariances[MAX_CLUSTERS][2][2];  // Covariance matrices
    double weights[MAX_CLUSTERS];       // Mixture weights
    int num_clusters;                   // Number of clusters
} GMM;

void fit_gmm(GMM *model, double data[][2], int n, int k);
void print_gmm(const GMM *model);

#endif  // GMM_H
