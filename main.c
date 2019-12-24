#include "mnist.h"
#include "init_network.h"
#include "forward.h"
#include "backward.h"
#include "loss.h"

#include <stdio.h>
int main(void)
{
	int batch_size = 100;
	int iter_num = 1000;
	int i=0;
	int j=0;
	int k=0;
    
	// Load the mnist dataset
    load_mnist();

	init_INPUT_LAYER();
	init_HIDDEN_LAYER();
	
	for (i=0; i<iter_num;i++) {	
		
		/* Choose image randomly to train */
		random_batch(batch_size);
		
		/* Forward */
		L1_forward(train_image, batch_size);
		L2_forward(batch_size);
	
		/* Calculate the loss of batch */
		//batch_cross_entropy(one_hot_train_label, batch_size);
		
		/* Backward */
		backward(train_image, one_hot_train_label, batch_size);
		
		/* Update weight in each layer */
		update_key(batch_size);
		predict(train_image, one_hot_train_label, batch_size);
	
	}
	
	test();
    
	return 0;
}
