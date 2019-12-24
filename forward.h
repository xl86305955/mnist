#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "activation.h"
/*
#define BATCH_SIZE 100

float out1[BATCH_SIZE][HIDDEN_SIZE];
float out2[BATCH_SIZE][OUTPUT_SIZE];
*/


void L1_forward(double image[][SIZE], int BATCH_SIZE) {
	int i = 0;
	int j = 0;
	int k = 0;
	int tag;
	for (k = 0; k < BATCH_SIZE; k++) {
		tag = batch_label[k];
		for (i = 0; i < HIDDEN_SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				a1[k][i] += image[tag][j] * layer1.w1[j][i]; 
			}
		}
	}
	
	/*
 	 *	a1 = ax+b
 	 *	z1 = relu(a1)
 	 */

	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			a1[i][j] += layer1.b1[j];
			z1[i][j] = relu(a1[i][j]);
		}
	}
}
 
void L2_forward(int BATCH_SIZE) {
	int i = 0;
	int j = 0;
	int k = 0;
	for (k = 0; k < BATCH_SIZE; k++) {
		for (i = 0; i < OUTPUT_SIZE; i++) {
			for (j = 0; j < HIDDEN_SIZE; j++) {
				a2[k][i] += z1[k][j] * layer2.w2[j][i]; 
			}	
		}
	}
	for (i=0; i<BATCH_SIZE; i++) {
		for (j=0; j<OUTPUT_SIZE; j++) {
			a2[i][j] += layer2.b2[j];
		}
		softmax(i);
	}
}

void predict(double image[][SIZE], int one_hot_label[][OUTPUT_SIZE], int BATCH_SIZE) {
	int i;
	int j;
	int label;
	int cnt = 0;
	int guess = 0;
	double max_out = 0;
	L1_forward(image, BATCH_SIZE);
	L2_forward(BATCH_SIZE);
	
	for(i=0; i<BATCH_SIZE; i++) {
		max_out = 0;
		guess = 0;
		label = batch_label[i];
		for (j=0; j<OUTPUT_SIZE; j++) {
			if (y[i][j] > max_out) {
				max_out = y[i][j];
				guess = j; 
			}	
		}
		if (one_hot_label[label][guess] == 1) {
			cnt++;
		}	
	}
	printf("precision:%d%\n", cnt);
	cnt = 0;
}

void test() {
	int k = 0;
	int i = 0;
	int j = 0;
	int tag;
	int label[10];
	double x_max = 0;
	int guess = 0;
	int answer = 0;

	double t1[10][HIDDEN_SIZE];
	double t2[10][OUTPUT_SIZE];

	srand(time(NULL));
	for (i=0; i<10; i++) {
		label[i] = rand()%NUM_TEST;
	}
	
	/* L1 forward */
	for (i=0; i<10; i++) {
		tag = label[i];
		for (j=0 ;j<HIDDEN_SIZE; j++) {
			for (k=0; k<SIZE; k++) {
				t1[i][j] += test_image[tag][k] * layer1.w1[k][j];
			}
		}
	}
	for (i=0; i<10; i++) {
		for (j=0; j<HIDDEN_SIZE; j++) {
			t1[i][j] += layer1.b1[j];
			t1[i][j] = relu(t1[i][j]);
		}
	}
	/* L2 forward */
	for (k = 0; k < 10; k++) {
		for (i = 0; i < OUTPUT_SIZE; i++) {
			for (j = 0; j < HIDDEN_SIZE; j++) {
				t2[k][i] += t1[k][j] * layer2.w2[j][i]; 
			}	
		}
	}
	for (i=0; i<10; i++) {
		for (j=0; j<OUTPUT_SIZE; j++) {
			t2[i][j] += layer2.b2[j];
		}
	}
	
	for (i=0; i<10; i++) {
		tag = label[i];
		for (j=0; j<SIZE; j++) {
			if (test_image[tag][j] > 0) {
				printf("*");
			}
			else printf(" ");
			if (j%28 == 0) {
				printf("\n");

			}
		}
		for (k=0; k<10; k++) {
			if (t2[i][k] > x_max) {
				x_max = t2[i][k];
				guess = k;
			}
			if (one_hot_test_label[tag][k] == 1) {
				answer = k;
			}
		}
		printf("\npredict:%d\tanswer:%d\n", guess, answer);
		guess = 0;
		answer = 0;
		x_max = 0;
	}	

}


