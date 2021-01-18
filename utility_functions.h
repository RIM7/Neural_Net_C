#include<math.h>

//int row, col, row1, col1, row2, col2;

//parameters to be changed for row and columns.
double **t_mat(double **actual, int row, int col){
  double **trans = calloc(sizeof(int*), col); for(int i=0; i<col; i++) trans[i]=calloc(sizeof(int*), row);
  for(int i=0; i<col; i++) for(int j=0; j<row; j++) trans[i][j] = actual[j][i];
	return (double **)trans;
}

//=============================================================================================================
double **t_vect(double *actual, int row, int col){   
  double **trans = calloc(sizeof(int*), col); for(int i=0; i<col; i++) trans[i]=calloc(sizeof(int*), 1);
  for(int i=0; i<col; i++) for(int j=0; j<1; j++) trans[i][j] = actual[i];
  return (double **)trans;
}

//=============================================================================================================
double **mul(double **m1, double **m2, int row1, int col1, int row2, int col2) {
	int i,j,k; double **mult=malloc(sizeof(int*) * row1); for(i=0; i<row1; i++) { mult[i] = malloc(sizeof(int*) * col2); }

	for(int i=0; i<row1; i++){ for(j=0; j<col2; ++j){ mult[i][j]=0; } }
	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i=0; i<row1; ++i) { for(j=0; j<col2; ++j){ for(k=0; k<col1;++k){ mult[i][j]+=m1[i][k]*m2[k][j]; } } }

  //printf("\n\nInside mul\n");
  //for(int i=0; i<row1; i++) { for(int j=0; j<col2; j++) printf("%lf ", mult[i][j]); printf("\n"); }

	return mult;
}

//=============================================================================================================
double **add_bias(double **mat, double bias, int row, int col){
  for(int i=0; i<row; i++){ for(int j=0; j<col; j++) mat[i][j] += bias; }
  return mat;
}

//=============================================================================================================
double **logit(double **activated, int row1, int col2){
	for(int i=0; i<row1; i++){ 
    for(int j=0; j<col2; j++){ 
      activated[i][j] = 1 / (1 + pow(2.718281828, -activated[i][j]));
    } 
  }
	return activated;
}


/*
double **t_mat(double **actual){
  printf("\n\nactual=\n"); for(int i=0; i<row; i++) {for(int j=0; j<col; j++) printf("%.2lf  ", actual[i][j]); printf("\n"); }
  printf("\n\ntrans=\n"); for (int i = 0; i<col;++i){for(int j = 0; j < row; ++j) printf("%.2lf  ",trans[i][j]); printf("\n"); }
}
double **t_vect(double *actual){
  printf("\n\nactual=\n"); for(int i=0; i<col; i++) printf("%.2lf  ", actual[i]);
  printf("\n\ntrans=\n"); for (int i = 0; i<col;++i){for(int j = 0; j < row; ++j) printf("%.2lf  ", trans[i][j]); printf("\n"); }
}

double **add_bias(double **mat, double bias, int row, int col){
  for(int k=0; k<row; k++){ for(int l=0; l<col; l++) printf("%lf ", mat[k][l]); printf("\n"); }
}

*/
