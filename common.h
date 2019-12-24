#ifndef common
#define common

#define SIZE 784
#define NUM_TRAIN 60000
#define NUM_TEST 10000

double train_image[NUM_TRAIN][SIZE];
double test_image[NUM_TEST][SIZE];
int  train_label[NUM_TRAIN];
int test_label[NUM_TEST];

// Label with one hot key
int one_hot_train_label[NUM_TRAIN][10]= {0};
int one_hot_test_label[NUM_TEST][10]= {0};

int batch_label[100];


#define HIDDEN_SIZE 100
#define OUTPUT_SIZE 10
struct input_layer {
        double w1[SIZE][HIDDEN_SIZE];
        double b1[HIDDEN_SIZE];
		double g_w1[SIZE][HIDDEN_SIZE];
        double g_b1[HIDDEN_SIZE];
};

struct hidden_layer {
        double w2[HIDDEN_SIZE][OUTPUT_SIZE];
        double b2[OUTPUT_SIZE];
        double g_w2[HIDDEN_SIZE][OUTPUT_SIZE];
        double g_b2[OUTPUT_SIZE];
};

struct input_layer layer1;
struct hidden_layer layer2;

// layer output 784*100_100*10_10*1
double a1[100][HIDDEN_SIZE];
double z1[100][HIDDEN_SIZE];
double a2[100][OUTPUT_SIZE];
double y[100][OUTPUT_SIZE];

#endif

