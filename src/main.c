#include <stdio.h>
#include "gmm.h"

void demo_tiny_reducer_db() {
    // Sample data (2D points)
    double data[6][2] = { {1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0},
                          {8.0, 7.0}, {9.0, 6.0}, {10.0, 8.0} };
    GMM model;
    init_gmm(&model, 2);  // Initialize with 2 clusters


    // Fit GMM with 2 clusters
    fit_gmm(&model, data, 6, 2);

    // Save to DB
    save_gmm_to_db(&model);

    for (int i = 0; i < 6; ++i) {
        update_gmm(&model, new_data[i]);
        printf("After adding point (%f, %f):\n", new_data[i][0], new_data[i][1]);
        print_gmm(&model);
    }
    
    // Load from DB and print
    GMM loaded_model;
    load_gmm_from_db(&loaded_model);

    print_gmm(&loaded_model);

    for (int i = 0; i < 6; ++i) {
        update_gmm(&model, new_data[i]);
        printf("After adding point (%f, %f):\n", new_data[i][0], new_data[i][1]);
        print_gmm(&model);
    }

    /** Cluster querying. 
    */
    // Query cluster 0 details
    printf("\n--- Querying Cluster 0 ---\n");
    query_cluster(&model, 0);

    // Query density at a point for cluster 1
    double point[2] = {5.0, 5.0};
    printf("\nDensity at point (5.0, 5.0) in Cluster 1: %f\n", 
           query_density(&model, point, 1));

    // Query density at the same point for the entire mixture
    printf("Density at point (5.0, 5.0) for the entire mixture: %f\n", 
           query_density(&model, point, -1));
        
}

int main() {
    demo_tiny_reducer_db();    
    return 0;
}
