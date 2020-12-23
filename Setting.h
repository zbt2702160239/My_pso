//
//  Setting.h
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#ifndef Setting_h
#define Setting_h

#include <stdlib.h>

#define MAX_SWARM_SIZE 100//最大粒子个数
#define MIN_INERTIA_WEIGHT 0//最小惯性权重
#define MAX_INERTIA_WEGHT 1//最大惯性权重

//随机游动，随机数的产生
#define RANDOM_UNIFORM() (rand()/(double)RAND_MAX)
#define RANDOM_UNIFORM_INT(s) (rand()%s)


typedef struct {
    int swarm_size;//粒子个数
    int dim;//粒子所拥有的维度
    double *range_lo_swarm_sport;//每一个维度粒子运动范围
    double *range_hi_swarm_sport;
    
    int algorithm_max_step;//算法最多执行次数
    int current_step;//算法当前执行到第几步
    
    double cognitive_ability;//粒子认知系数
    double social_affect;//全局解对粒子影响系数
    double max_inertia_weight;//最大惯性权重
    double min_inertia_weight;//最小惯性权重
    
    int bounds;//判断粒子是否又越界情况，如果发生了越界执行相关操作
    
    int neighborhood_strategy;//相邻元素的拓扑结构
    int neighborhood_size;//相邻元素个数
    int inertia_weight_strategy;//惯性权重计算方式
    double goal;//为了达到这个目标
    int print_every;
}setting;

typedef double (*eval_fun)(double* ,setting*);

setting *setting_param(int dim,double range_lo,double range_hi,int neighbor_strategy);//设置参数
void free_setting(setting *setting);//释放设置的参数

#endif /* Setting_h */
