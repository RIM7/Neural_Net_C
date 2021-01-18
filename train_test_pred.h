double ***forward_prop(double ***gen_ip, int j){
  gen_ip = calloc(sizeof(int *), no_of_layers-1);
  for (int i=0 ; i<no_of_layers-1 ; i++){
    double **trans, **ip, **mult, **biased;

    trans = t_mat(records[i],nodes_in_layer[i],nodes_in_layer[i+1]); 
    if(i==0) ip = t_vect(ip_samples[j], 1, nodes_in_layer[i]);    
    else     ip = gen_ip[i-1];

    mult = mul(trans, ip, nodes_in_layer[i+1], nodes_in_layer[i], nodes_in_layer[i], 1);
    biased = add_bias(mult, bias[i], nodes_in_layer[i+1], 1);
    double **log = logit(biased, nodes_in_layer[i+1], 1);
    gen_ip[i] = log;
  }
  
  printf("\nForward prop \n");
  for(int i=0; i<no_of_layers-1; i++) {
    for(int j=0;j<nodes_in_layer[i+1];j++){for(int k=0;k<1;k++)printf("%lf",gen_ip[i][j][k]);printf("\n");} 
    printf("\n");
  }

  return gen_ip;
}

void backward_prop(double ***gen_ip, int j){
  double ita = 0.5;
  //2nd Layer.
  double dEtotal_doutO1 = -op_samples[j][0] + gen_ip[1][0][0];      //=-0.01+0.751365=0.741365
  double doutO1_dNetO1  = gen_ip[1][0][0] * (1-gen_ip[1][0][0]);    //=0.751365*(1-0.751365)=0.186815
  double dNetO1_dw5     = gen_ip[0][0][0];                          //=0.593269 
  double dNetO1_dw6     = gen_ip[0][1][0];                          //=  0.596884
  
  double dEtotal_dw5    = dEtotal_doutO1 * doutO1_dNetO1 * dNetO1_dw5;  //= 0.082166
  double dEtotal_dw6    = dEtotal_doutO1 * doutO1_dNetO1 * dNetO1_dw6;  //= 0.0826676

  double dEtotal_doutO2 = -op_samples[j][1] + gen_ip[1][1][0];      //= -0.99+0.772928 = -0.217072
  double doutO2_dNetO2  = gen_ip[1][1][0] * (1 - gen_ip[1][1][0]);  //=0.772928(1-0.772928)=0.175510
  double dNetO2_dw7     =  dNetO1_dw5;                              //=  0.593269 
  double dNetO2_dw8     =  dNetO1_dw6;                              //=  0.596884

  double dEtotal_dw7    = dEtotal_doutO2 * doutO2_dNetO2 * dNetO2_dw7;  //= -0.0226025
  double dEtotal_dw8    = dEtotal_doutO2 * doutO2_dNetO2 * dNetO2_dw8;  //= -0.0227402

  //Update weights of 2nd layer.
  //w[i] ( wi_new ) = wi_old – ita*dEtotal_dwi
  //records[1][0][0] = 0.40; //w5   records[1][0][1] = 0.50; //w7
  //records[1][1][0] = 0.45; //w6   records[1][1][1] = 0.55; //w8
  //printf("\n%lf  %lf  %lf  %lf", dEtotal_dw5, dEtotal_dw6, dEtotal_dw7, dEtotal_dw8);
  
  records[1][0][0] -= ita * dEtotal_dw5;  records[1][0][1] -= ita * dEtotal_dw7;
  records[1][1][0] -= ita * dEtotal_dw6;  records[1][1][1] -= ita * dEtotal_dw8;

  printf("\nUpdated weights at Layer2");
  printf("\n%lf  ", records[1][0][0]); printf("%lf", records[1][0][1]);
  printf("\n%lf  ", records[1][1][0]); printf("%lf", records[1][1][1]);

  //1st layer.
  double dNetO1_doutH1  = records[1][0][0];
  double dNetO2_doutH1  = records[1][0][1];
  double dEtotal_doutH1 = dEtotal_doutO1 * doutO1_dNetO1 * dNetO1_doutH1 + dEtotal_doutO2 * doutO2_dNetO2 * dNetO2_doutH1;
  //                    = 0.7413*0.1868*0.3589 +  -0.217*0.175*-0.022 = 0.05056
  double doutH1_dNetH1  = gen_ip[0][0][0] * (1-gen_ip[0][0][0]);         //=0.593269(1-0.593269 )=0.2413007
  double dNetH1_dw1     = ip_samples[j][0];                              //=  0.05
  double dNetH1_dw2     = ip_samples[j][1];                              //=  0.10

  double dEtotal_dw1    = dEtotal_doutH1	*	doutH1_dNetH1	*	dNetH1_dw1;  //= 0.000610  
  double dEtotal_dw2    = dEtotal_doutH1	*	doutH1_dNetH1	*	dNetH1_dw2;  //= 0.001220

  double dNetO1_doutH2  = records[1][1][0];
  double dNetO2_doutH2  = records[1][1][1];
  double dEtotal_doutH2 = dEtotal_doutO1 * doutO1_dNetO1 * dNetO1_doutH2 +  dEtotal_doutO2 * doutO2_dNetO2  * dNetO2_doutH2;
  //                    =  0.741*0.186*0.408 + -0.217*0.175*-0.022 = =  0.0570
  double doutH2_dNetH2  =  gen_ip[0][1][0] * (1-gen_ip[0][1][0]);        //=0.596884*(1-0.596884)=0.240613
  double dNetH2_dw3     =  ip_samples[j][0];                             //= 0.05
  double dNetH2_dw4     =  ip_samples[j][0];                             //= 0.10

  double dEtotal_dw3    =  dEtotal_doutH2 * doutH2_dNetH2 * dNetH2_dw3;  //=  0.0006877
  double dEtotal_dw4    =  dEtotal_doutH2 * doutH2_dNetH2 * dNetH2_dw4;  //=  0.0013754

  //Update weights of 1st layer.
  //records[0][0][0] = 0.15; //w1   records[0][0][1] = 0.25; //w3
  //records[0][1][0] = 0.20; //w2   records[0][1][1] = 0.30; //w4
  records[0][0][0] -= ita * dEtotal_dw1;  records[0][0][1] -= ita * dEtotal_dw3;
  records[0][1][0] -= ita * dEtotal_dw2;  records[0][1][1] -= ita * dEtotal_dw4;

  printf("\n\nUpdated weights at Layer1");
  printf("\n%lf  ", records[0][0][0]); printf("%lf", records[0][0][1]);
  printf("\n%lf  ", records[0][1][0]); printf("%lf", records[0][1][1]);


}



/*
    //Forward Propagation.
		for (int i=0 ; i<no_of_layers-1 ; i++){
      //printf("\n=====================================");

      printf("\n\ntranspose of the weight matrix= \n"); 
      for(int k=0;k<nodes_in_layer[i+1];k++){ for(int l=0;l<nodes_in_layer[i];l++)printf("%lf ",trans[k][l]);printf("\n");}

      if(i==0){ printf("\n\ntranspose of the initial inputs= \n"); 
        for(int k=0;k<nodes_in_layer[i];k++){for(int l=0;l<1;l++)printf("%lf ",ip[k][l]);printf("\n");} }
      else{ printf("\n\ngen_ip = \n"); 
        for(int k=0;k<nodes_in_layer[i];k++){for(int l=0;l<1;l++)printf("%lf ",ip[k][l]);printf("\n");} }

      printf("\n\nmultiplication = \n");
      for(int k=0;k<nodes_in_layer[i+1];k++){for(int l=0;l<1;l++)printf("%lf ",mult[k][l]);printf("\n");}

      //printf("\n\nAfter adding bias = \n");
      //for(int k=0;k<nodes_in_layer[i+1];k++){for(int l=0;l<1;l++)printf("%lf ",biased[k][l]);printf("\n");}

      //printf("\n\nAfter applying logit = \n");
      //for(int k=0; k<nodes_in_layer[i+1]; k++){for(int l=0;l<1;l++)printf("%lf ",log[k][l]);printf("\n");
    }
    for(int i=0; i<no_of_layers-1; i++) {
      for(int j=0;j<nodes_in_layer[i+1];j++){for(int k=0;k<1;k++)printf("%lf",gen_ip[i][j][k]);printf("\n");}
      printf("\n");
    }
*/