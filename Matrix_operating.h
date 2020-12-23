//
//  Matrix_operating.h
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#ifndef Matrix_operating_h
#define Matrix_operating_h

#include <stdio.h>
#include "Setting.h"
double **init_matrix(setting *pso_setting);//矩阵构造
void free_matrix(double **matrix,setting *pso_setting);//矩阵释放

#endif /* Matrix_operating_h */
