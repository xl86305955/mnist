#include <stdio.h>
#include <math.h>
#include "common.h"

#define delta 0.0000001

void batch_cross_entropy(int one_hot_label[][10], int BATCH_SIZE) {
	int i = 0;
    int j = 0;
    int k = 0;
	int tag;
	int label;
    double loss[BATCH_SIZE];
    double batch_loss = 0;
	double tmp = 0;		
    for (k = 0; k < BATCH_SIZE; k++) {
		label = batch_label[k];
		for (i = 0; i < OUTPUT_SIZE; i++) {
            if (one_hot_label[label][i] == 1) {
				tmp = y[k][i];
				loss[k] = log(tmp);
			}
		}
        batch_loss += loss[k];
   	}
    batch_loss /= -BATCH_SIZE;
	printf("loss:%lf\n", batch_loss);
	batch_loss = 0;
	tmp = 0;
}

