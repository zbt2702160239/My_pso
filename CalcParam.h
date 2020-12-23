//
//  CalcParam.h
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#ifndef CalcParam_h
#define CalcParam_h

#include <stdio.h>
#include "Setting.h"
int calc_swarm_size(int dim);//根据维度计算粒子数
double calc_inertia_linearly_decreasing(setting *pso_setting);//计算线性梯度下降
double calc_adaptation(double *pos,setting *setting);//计算适应性
double calc_adaptation_rosenbrock(double *pos,setting *setting);
double calc_adaptation_griewank(double *pos,setting *setting);
double calc_adaption_rastrigin(double *pos,setting *setting);
#endif /* CalcParam_h */
