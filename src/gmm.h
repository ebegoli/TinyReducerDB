
#ifndef GMM_H
#define GMM_H

typedef struct {
    float mean;
    float variance;
} GMM;

// Function to compute the probability of a given input for the GMM
float gmm_probability(GMM *gmm, float x);

#endif
