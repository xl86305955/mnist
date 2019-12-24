#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

#define MIN -0.02
#define MAX 0.02


/*
struct INPUT_LAYER {
	float w1[INPUT_SIZE][HIDDEN_SIZE];
	float b1[HIDDEN_SIZE];
};

struct HIDDEN_LAYER {
	float w2[HIDDEN_SIZE][OUTPUT_SIZE];
	float b2[OUTPUT_SIZE];
};

struct INPUT_LAYER layer1;
struct HIDDEN_LAYER layer2;
*/

float random_float() {
	return (((float)rand() / RAND_MAX) * (MAX-MIN)) + MIN;
}

void random_batch(int batch_size) {
	int i=0;
	for (i=0; i<batch_size; i++) {
		batch_label[i] = rand()%NUM_TRAIN;
	}
}


void init_INPUT_LAYER() {
	int i = 0;
	int j = 0;
	srand(time(NULL));
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j< HIDDEN_SIZE; j++) {
			layer1.w1[i][j] = random_float();
			layer1.g_w1[i][j] = 0;
		}
	}
	for (j = 0; j < HIDDEN_SIZE; j++) {
		layer1.b1[j] = 0;
		layer1.g_b1[j] = 0;
	}
}




void init_HIDDEN_LAYER () {
	int i = 0;
	int j = 0;
	srand(time(NULL));
	for (i = 0; i < HIDDEN_SIZE; i++) {
		for (j = 0; j< OUTPUT_SIZE; j++) {
			layer2.w2[i][j] = random_float();
			layer2.g_w2[i][j] = 0;
		}
	}
	for (j = 0;j < OUTPUT_SIZE; j++) {
		layer2.b2[j] = 0;
		layer2.g_b2[j] = 0;
	}
}

