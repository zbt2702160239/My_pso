//
//  Setting.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//
#include <stdlib.h>
#include "Setting.h"
#include "CalcParam.h"
setting *setting_param(int dim,double range_lo,double range_hi,int neighbor_strategy)//设置参数
{
    setting *pso_setting=(setting *)malloc(sizeof(setting));
    if(pso_setting==NULL){
        return NULL;
    }
    //根据参数设置
    pso_setting->dim=dim;
    pso_setting->range_lo_swarm_sport=(double*)malloc(pso_setting->dim*sizeof(double));//为每一个维度申请下界
    if(pso_setting->range_lo_swarm_sport==NULL){
        free(pso_setting);
        return NULL;
    }
    pso_setting->range_hi_swarm_sport=(double*)malloc(pso_setting->dim*sizeof(double));//为每一个维度申请上界
    if(pso_setting->range_hi_swarm_sport==NULL){
        free(pso_setting);
        return NULL;
    }
    for(int i=0;i<pso_setting->dim;i++){//为每一个维度设置界限
        pso_setting->range_lo_swarm_sport[i]=range_lo;
        pso_setting->range_hi_swarm_sport[i]=range_hi;
    }
    
    //默认设置
    pso_setting->algorithm_max_step=100000;
    pso_setting->cognitive_ability=1.496;
    pso_setting->social_affect=1.496;
    pso_setting->max_inertia_weight=0.7298;
    pso_setting->min_inertia_weight=0.3;
    pso_setting->bounds=1;
    pso_setting->neighborhood_strategy=neighbor_strategy;//0随机 1环形 2全局
    pso_setting->inertia_weight_strategy=1;//梯度下降策略
    pso_setting->goal=1e-5;
    pso_setting->print_every=1;//输出策略
    //计算设置
    pso_setting->swarm_size=calc_swarm_size(pso_setting->dim);
    return pso_setting;
}
void free_setting(setting *setting)//释放设置的参数
{
    free(setting);
}
