//
//  Matrix_operating.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#include "Matrix_operating.h"
double **init_matrix(setting *pso_setting){//矩阵构造
    double **matrix=(double **)malloc(pso_setting->swarm_size*sizeof(double*));
    for(int i=0;i<pso_setting->swarm_size;i++){
        matrix[i]=(double*)malloc(pso_setting->dim*sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix,setting *pso_setting){//矩阵释放
    for(int i=0;i<pso_setting->swarm_size;i++){
        free(matrix[i]);
    }
    free(matrix);
}
