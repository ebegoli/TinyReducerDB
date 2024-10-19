#include <stdio.h>
#include "gmm.h"

void demo_tiny_reducer_db() {
    // Sample data (2D points)
    double data[6][2] = { {1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0},
                          {8.0, 7.0}, {9.0, 6.0}, {10.0, 8.0} };
    GMM model;

    // Fit GMM with 2 clusters
    fit_gmm(&model, data, 6, 2);

    // Save to DB
    save_gmm_to_db(&model);

    // Load from DB and print
    GMM loaded_model;
    load_gmm_from_db(&loaded_model);
    print_gmm(&loaded_model);
}

int main() {
    demo_tiny_reducer_db();    
    return 0;
}
