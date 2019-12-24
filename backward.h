#include <string.h>
#include <math.h>
#include "common.h"
#include "activation.h"

void backward(double image[][SIZE], int one_hot_label[][10], int BATCH_SIZE) {
	int i = 0;
	int j = 0;
	int k = 0;
	
	double tmp;
	int label;

	float z1_t[HIDDEN_SIZE][BATCH_SIZE];

	double w2_t[OUTPUT_SIZE][HIDDEN_SIZE];

	double da1[BATCH_SIZE][HIDDEN_SIZE];
	double dz1[BATCH_SIZE][HIDDEN_SIZE];
	double dy[BATCH_SIZE][OUTPUT_SIZE];

	double image_t[SIZE][BATCH_SIZE];
	
	/* Transpose of z1 */
	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			z1_t[j][i] = z1[i][j];
		}
	}
	/* 
 	 * Calculate dy
 	 * dy = (y - t) / BATCH_SIZE
 	 */
	for (k=0; k<BATCH_SIZE; k++) {
		label = batch_label[k];
		for (i=0; i<OUTPUT_SIZE; i++) {
			if (one_hot_label[label][i] == 1) {
				dy[k][i] = (y[k][i] -  1.0) / (double)BATCH_SIZE;
			}
			else {
				dy[k][i] = y[k][i] / (double)BATCH_SIZE;
			}
		}
	}

	/* 
 	 * Gradient of w2
 	 * g_w2 = dot(z1_t, dy)
 	 */
	for (k=0; k<HIDDEN_SIZE; k++) {
		for (i=0; i<OUTPUT_SIZE; i++) {
			for (j=0; j<BATCH_SIZE; j++) {
				layer2.g_w2[k][i] += z1_t[k][j] * dy[j][i];
			}
		}
	}

	/* Backward for b2 */
	for (i=0; i<OUTPUT_SIZE; i++) {
		for (j=0; j<BATCH_SIZE; j++) {
			layer2.g_b2[i] += dy[j][i];
		}
	}
	
	/* Transepose of w2 */
	for (i = 0; i<HIDDEN_SIZE; i++) {
		for (j=0; j<OUTPUT_SIZE; j++) {
			w2_t[j][i] = layer2.w2[i][j];
		}
	}
	
	/*  
 	 * Calculate dz1
     * dz1 = dot(dy, w2_t) 
     */
	for (k=0; k<BATCH_SIZE; k++) {
		for (i=0; i<HIDDEN_SIZE; i++) {
			for (j=0; j<OUTPUT_SIZE; j++) {
				dz1[k][i] += dy[k][j] * w2_t[j][i];
			}
		}
	}

	/* Calculate da1 */
	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			if (relu_mask(a1[i][j])) 
				da1[i][j] = dz1[i][j];
			else 
				da1[i][j] = 0;
		}
	}
	
	/* Transpose of image */
	for (i=0; i<BATCH_SIZE; i++) {
		label = batch_label[i];
		for (j=0; j<SIZE; j++) {
			image_t[j][i] = image[label][j];
		}
	}
	/* Gradient of w1 */	
	for (k=0; k<SIZE; k++) {
		for (i=0;i<HIDDEN_SIZE; i++) {
			for (j=0; j<BATCH_SIZE; j++) {
				layer1.g_w1[k][i] += image_t[k][j] * da1[j][i];
			}
		}
	}
	
	/* Gradient of b1 */
	for (i=0; i<HIDDEN_SIZE; i++) {
		for (j=0; j<BATCH_SIZE;j++) {
			layer1.g_b1[i] += da1[j][i];
		}
	}
	
	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			da1[i][j] = 0;
			dz1[i][j] = 0;
		}
	}
	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<OUTPUT_SIZE; j++) {
			dy[i][j] = 0;
		}
	}

}

void update_key(int BATCH_SIZE) {
	int i=0;
	int j=0;
	float lr = 0.1;
	
	/* Update w1 */
	for (i=0; i<SIZE; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			layer1.w1[i][j] -= lr * layer1.g_w1[i][j];
		}
	}
	
	/* Update b1 */
	for (i=0; i<HIDDEN_SIZE; i++) {
		layer1.b1[i] -= lr * layer1.g_b1[i];
	}
	
	/* Update w2 */
	for (i=0; i<HIDDEN_SIZE; i++) {
		for (j=0; j<OUTPUT_SIZE; j++) {
			layer2.w2[i][j] -= lr * layer2.g_w2[i][j];
		}
	}
	
	/* Update b2 */
	for (i=0; i<OUTPUT_SIZE; i++) {
		layer2.b2[i] -= lr * layer2.g_b2[i]; 
	}

	/* Clear the gradient of layer1 */
	memset(layer1.g_w1, 0, sizeof(layer1.g_w1[0][0]) * SIZE * HIDDEN_SIZE);
	memset(layer1.g_b1, 0, sizeof(layer1.g_b1));

	/* Clear the gradient of layer2 */	
	memset(layer2.g_w2, 0, sizeof(layer2.g_w2[0][0]) * HIDDEN_SIZE * OUTPUT_SIZE);
	memset(layer2.g_b2, 0, sizeof(layer2.g_b2));
	
	memset(a1, 0, sizeof(a1[0][0]) * BATCH_SIZE * HIDDEN_SIZE);
	memset(z1, 0, sizeof(z1[0][0]) * BATCH_SIZE * HIDDEN_SIZE);

	memset(a2, 0, sizeof(a2[0][0]) * BATCH_SIZE * OUTPUT_SIZE);

	
}

