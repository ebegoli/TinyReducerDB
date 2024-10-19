
#include <stdio.h>
#include "gmm.h"

int main() {
    GMM test_gmm = {0, 1};  // Mean=0, Variance=1
    float x = 0.5;
    printf("P(x=%.2f) = %f\n", x, gmm_probability(&test_gmm, x));
    return 0;
}
