#ifndef GMM_H
#define GMM_H

#define MAX_CLUSTERS 5  // Max number of clusters

typedef struct {
    double means[MAX_CLUSTERS][2];      // Mean vectors (2D case)
    double covariances[MAX_CLUSTERS][2][2];  // Covariance matrices
    double weights[MAX_CLUSTERS];       // Mixture weights
    int cluster_counts[MAX_CLUSTERS];   // Number of points assigned to each cluster
    int num_clusters;                   // Number of clusters
} GMM;

void fit_gmm(GMM *model, double data[][2], int n, int k);
void print_gmm(const GMM *model);
void update_gmm(GMM *model, double new_point[2]);  // For incremental updates

#endif  // GMM_H
