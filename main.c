#include <stdio.h>
#include<stdlib.h>
#include "take_inputs.h"
#include "utility_functions.h"
#include "train_test_pred.h"

double current_error;

int main(void) {

  // Take the inputs. Currently, the inuts are hardcoded, i.e. written manually.
  take_all_inputs();    
  
  print_all_inputs();
  

  // We train the model on the all the samples.
	for (int j = 0 ; j < samples ; j++ ) {
    int epoch = 0;

    // For each sample, we try to reduce the amount of error by running the forward and 
    // backward propagation.
    while(epoch <= 6000) {
      double ***gen_ip;
      gen_ip = forward_prop(gen_ip, j);   //Forward Propagation.

      double prev_error;
      if(epoch==0) prev_error = 99.0;
      else prev_error = current_error;

      // Error calculation
      current_error = 0.0;
      for (int k = 0 ; k < nodes_in_layer[no_of_layers-1] ; k++ ) {
        double temp=(op_samples[0][k]-gen_ip[no_of_layers-2][k][0]);
        temp = temp * temp; current_error += temp * 0.5;
      }

      // If previous error is less than current error, then the error has reached a
      // local minima. So we break at this point.
      if(prev_error <= current_error) { 
        printf("%lf %lf", prev_error, current_error);
        current_error = prev_error; break; 
      }

      //Printing the error and weights after each 3000 epochs.
      if(epoch%3000==0){
        printf("\n========================================\n");
        printf("\nerror = %lf\n",current_error);
        
        printf("\nUpdated weights at Layer2");
        printf("\n%lf  ", records[1][0][0]); printf("%lf", records[1][0][1]);
        printf("\n%lf  ", records[1][1][0]); printf("%lf", records[1][1][1]);      

        printf("\n\nUpdated weights at Layer1");
        printf("\n%lf  ", records[0][0][0]); printf("%lf", records[0][0][1]);
        printf("\n%lf  ", records[0][1][0]); printf("%lf\n", records[0][1][1]);
      }
      backward_prop(gen_ip, j);   //back propagation.
      epoch += 1;
    }
  }
  
  return 0;
}