#include <stdio.h>
#include<stdlib.h>
#include "take_inputs.h"
#include "utility_functions.h"
#include "train_test_pred.h"


int main(void) {
  take_all_inputs();    
  //print_all_inputs();
  
	for (int j = 0 ; j < samples ; j++ ) {
    double ***gen_ip;
    gen_ip = forward_prop(gen_ip, j);   //Forward Propagation.

    backward_prop(gen_ip, j);           //Backward Propagation.
  }
  
  return 0;
}



