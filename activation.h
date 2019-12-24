#ifndef activation
#define activation

#include <stdio.h>
#include <math.h>
#include "common.h"

#define max(a, b) \
        ({__typeof__(a) _a = (a); \
         __typeof__(b) _b = (b); \
        _a > _b ? _a : _b; })

float sigmoid (float x) {
        return 1 / ( 1 + pow(M_E, -x));
}

double relu (double x) {
        if (x <= 0)
                return 0;
        else
                return x;
}

int relu_mask (double x) {
	if (x <= 0) 
		return 0;
	else 
		return 1;
}

void softmax(int k) {
	int i = 0;
	double x_max = 0;
	double sum = 0;
	double tmp[OUTPUT_SIZE];
	double exp_a[OUTPUT_SIZE];
	
	/* Find the largest value in layer2 output */
	for (i=0; i<OUTPUT_SIZE; i++) {
		if (a2[k][i] > x_max) 
			x_max = a2[k][i];
	}
	for (i=0; i<OUTPUT_SIZE; i++) {
		tmp[i] = a2[k][i] - x_max;		// Minus x_max to avoid overflow 
		exp_a[i] = pow(M_E, tmp[i]);
		sum += exp_a[i];
	}
	for (i=0; i<OUTPUT_SIZE; i++) {
		y[k][i] = exp_a[i] / sum;
	}
}

#endif
