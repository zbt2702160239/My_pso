//
//  CalcParam.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//
#include<stdlib.h>
#include <math.h>
#include "CalcParam.h"
#include "Setting.h"
int calc_swarm_size(int dim){//根据维度计算粒子数
    int size=10.+2.*sqrt(dim);
    return size>MAX_SWARM_SIZE?MAX_SWARM_SIZE:size;
}
double calc_inertia_linearly_decreasing(setting *pso_setting){//梯度下降计算
    int dec_stage=3*pso_setting->algorithm_max_step/4;
    if(pso_setting->current_step<dec_stage)
        return pso_setting->min_inertia_weight+(pso_setting->max_inertia_weight-pso_setting->min_inertia_weight)*(dec_stage-pso_setting->current_step)/dec_stage;
    else
        return pso_setting->min_inertia_weight;
}
double calc_adaptation(double *pos,setting *setting){
    double sum=0;
    for(int i=0;i<setting->dim;i++){
        sum += pow(pos[i], 2);
    }
    return sum;
}
double calc_adaptation_rosenbrock(double *pos,setting *setting){//不能使用梯度下降来计算getchar()!='\n'
    double sum=0;
    for(int d=0;d<setting->dim;d++){
        sum+=(100*pow(pos[d+1]-pow(pos[d], 2), 2)+pow(1-pos[d],2));
    }
    return sum;
}
double calc_adaptation_griewank(double *pos,setting *setting){
    double sum=0;
    double prod=1;
    for(int d=0;d<setting->dim;d++){
        sum+=pow(pos[d],2);
        prod*=cos(pos[d]/sqrt(d+1));
    }
    return sum/4000-prod+1;
}
double calc_adaption_rastrigin(double *pos,setting *setting){
    double sum=0;
    for(int i=0;i<setting->dim;i++){
        sum+=(pow(pos[i],2)-10*cos(2*M_PI*pos[i]));
    }
    return 10*setting->dim+sum;
}
