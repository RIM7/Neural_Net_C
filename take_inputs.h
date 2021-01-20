int no_of_layers, * nodes_in_layer, samples;
double **ip_samples; double **op_samples; double *** records; double *bias;

// This function creates the structure of the neural network.
void take_all_inputs(){
  no_of_layers = 3;
	nodes_in_layer = calloc(no_of_layers, sizeof(int *));
  nodes_in_layer[0] = 2; nodes_in_layer[1] = 2; nodes_in_layer[2] = 2;
  samples = 1;

	ip_samples = calloc(samples, sizeof(int*));
	for(int i=0; i<samples; i++) ip_samples[i] = calloc(nodes_in_layer[0], sizeof(int *));
	ip_samples[0][0] = 0.05;
  ip_samples[0][1] = 0.10;

	op_samples = calloc(samples, sizeof(int *)); 
	for(int i=0;i<samples;i++) op_samples[i] = calloc(nodes_in_layer[no_of_layers-1], sizeof(int *));
	op_samples[0][0] = 0.01;
  op_samples[0][1] = 0.99;

	records = calloc(no_of_layers-1, sizeof(int*));
	for(int i=0; i<no_of_layers-1; i++){
		records[i] = calloc(nodes_in_layer[i], sizeof(int*)); 
    for(int j=0;j<nodes_in_layer[i];j++) records[i][j] = calloc(nodes_in_layer[i+1], sizeof(int*)); 
	}

  records[0][0][0] = 0.15; //w1
  records[0][0][1] = 0.25; //w3
  records[0][1][0] = 0.20; //w2
  records[0][1][1] = 0.30; //w4

  records[1][0][0] = 0.40; //w5
  records[1][0][1] = 0.50; //w7
  records[1][1][0] = 0.45; //w6
  records[1][1][1] = 0.55; //w8

	bias = calloc(sizeof(int *), no_of_layers-1);
  bias[0] = 0.35; bias[1] = 0.60;
  
}

//=====================================================================
void print_all_inputs(){
	printf("\ninput samples:\n");
	for(int i=0; i<samples; i++){ 
    for(int j=0; j<nodes_in_layer[0]; j++) printf("%lf ", ip_samples[i][j]); 
    printf("\n");
  }
	printf("\noutput samples:\n"); 
  for(int i=0; i<samples; i++){ 
    for(int j=0; j<nodes_in_layer[no_of_layers-1]; j++) printf("%lf ", op_samples[i][j]); 
    printf("\n");
  }
	for(int i=0; i<no_of_layers-1; i++) { 
		printf("\nWeights at layer %d -> %d:\n", i, i+1); 
		for(int j=0;j<nodes_in_layer[i];j++){
      for(int k=0;k<nodes_in_layer[i+1];k++)printf("%lf ",records[i][j][k]);printf("\n"); 
    }
	}
  printf("\nbias = ");
  for(int i=0; i<no_of_layers-1; i++) printf("%lf ", bias[i]);
  printf("\n========================================\n");
}
