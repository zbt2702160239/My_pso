//
//  Pso_Algorithm.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/16.
//
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "Setting.h"
#include "Pso_Algorithm.h"
#include "Matrix_operating.h"
#include "CalcParam.h"
#include "Inform_fun.h"
void pso_algorithm(eval_fun fun,setting *setting,result *solution){
    //初始化需要用到的变量
    double **pos=init_matrix(setting);//粒子位置 横行粒子 竖行粒子所在维度 其中存储粒子所在维度的位置
    double **vel=init_matrix(setting);//粒子速度 横行粒子 竖行粒子所在维度 其中存储粒子速度
    double **pos_b=init_matrix(setting);//粒子最佳位置
    double **pos_nb=init_matrix(setting);//粒子相邻最佳位置
    double *fit=(double*)malloc(setting->swarm_size*sizeof(double));//粒子适应值
    double *fit_b=(double*)malloc(setting->swarm_size*sizeof(double));//粒子最佳适应值
    int *comm_net=(int*)malloc(setting->swarm_size*setting->swarm_size*sizeof(int));//粒子通讯网络
    srand((unsigned)time(NULL));//随机种子
    switch(setting->neighborhood_strategy){
        case 1:init_ring_neighbor(comm_net, setting);//初始化通信网络
            break;
        case 2:init_random_neighbor(comm_net, setting);//随机邻居
            break;
    }
    solution->currrent_achieve_obj=DBL_MAX;//为初始目标赋一个最大值
    
   
    //对每一个粒子初始化
    for(int i=0;i<setting->swarm_size;i++){
        for(int d=0;d<setting->dim;d++){
            int a=setting->range_lo_swarm_sport[d]+(setting->range_hi_swarm_sport[d]-setting->range_lo_swarm_sport[d])*RANDOM_UNIFORM();//在该维度中生成随机点
            int b=setting->range_lo_swarm_sport[d]+(setting->range_hi_swarm_sport[d]-setting->range_lo_swarm_sport[d])*RANDOM_UNIFORM();
            pos[i][d]=a;//在该维度位置
            vel[i][d]=(a-b)/2;//每一个维度速度微动
        }
        //初始粒子适应性
        fit[i]=fun(pos[i], setting);
        
        fit_b[i]=fit[i];//当前只知道最好适应是自己
        //更性全局最好位置和适应值
        if(fit[i]<solution->currrent_achieve_obj){
            solution->currrent_achieve_obj=fit[i];
            memmove((void*)solution->gbest,(void*)pos[i],sizeof(double)*setting->dim);
        }
    }
    double weight_inertia;
    int improved=1;
    for(int step=0;step<setting->algorithm_max_step;step++){
        setting->current_step=step;
        weight_inertia=calc_inertia_linearly_decreasing(setting);
        if(solution->currrent_achieve_obj<=setting->goal){//每运行一步需要判断当前完成度
            printf("Achieve the goal where is best fit @step=%d (current_achieve_obj=%.3e)",setting->current_step,solution->currrent_achieve_obj);
            break;
        }
        //toast_neighbor_random(comm_net, pos_nb, pos_b, fit, setting, solution,improved);//更新所有粒子邻居信息
        switch(setting->neighborhood_strategy){
            case 0:toast_neighbor_random(comm_net, pos_nb, pos_b, fit, setting, solution, improved);break;
            case 1:toast_neighbor_ring(comm_net, pos_nb, pos_b, fit, setting, solution);break;
            
            case 2:toast_neighbor_global(comm_net, pos_nb, pos_b, fit, setting, solution);break;
        }
        improved=0;//重新设置improved
        for(int i=0;i<setting->swarm_size;i++){
            for(int d=0;d<setting->dim;d++){
                //计算各种影响因素
                double r_e1=setting->social_affect*RANDOM_UNIFORM();//产生一个社会影响系数
                double r_e2=setting->cognitive_ability*RANDOM_UNIFORM();//产生一个认知能力影响系数
                 
                vel[i][d]=weight_inertia*vel[i][d] + r_e1 * (pos_b[i][d]-pos[i][d])+
                r_e2*(pos_nb[i][d]-pos[i][d]);//计算速度
                //更新位置
                pos[i][d]+=vel[i][d];
                //判断是否到达边界
                if(setting->bounds){//判断是否设置边界条件
                    if(pos[i][d]<setting->range_lo_swarm_sport[d]){
                        pos[i][d]=setting->range_lo_swarm_sport[d];//到达边界被冲为0
                        vel[i][d]=0;
                    }else if(pos[i][d]>setting->range_hi_swarm_sport[d]){
                        pos[i][d]=setting->range_lo_swarm_sport[d];
                        vel[i][d]=0;
                    }
                }else{
                    //没有设置边界条件，执行周期边界条件
                    if(pos[i][d]<setting->range_lo_swarm_sport[d]){
                        pos[i][d]=setting->range_hi_swarm_sport[d] - fmod(setting->range_lo_swarm_sport[d]-pos[i][d],setting->range_hi_swarm_sport[d]-setting->range_lo_swarm_sport[d]);
                        vel[i][d]=0;
                    }else if (pos[i][d]>setting->range_hi_swarm_sport[d]){
                        pos[i][d]=setting->range_lo_swarm_sport[d]-fmod(pos[i][d]-setting->range_hi_swarm_sport[d], setting->range_hi_swarm_sport[d]-setting->range_lo_swarm_sport[d]);
                        vel[i][d]=0;
                    }
                }
                //更新适应函数
                fit[i]=fun(pos[i], setting);
//                printf("Number %d adaption is %e.5\n",i,fit[i]);
//                printf("\n");
                //更新该粒子所到达的最优解
                if(fit[i]<fit_b[i]){
                    fit_b[i]=fit[i];
                    //更新最好位置
                    memmove((void*)pos_b[i],(void*)pos[i],sizeof(double)*setting->dim);
                }
                //是否到达更好的适应性
                if(fit[i]<solution->currrent_achieve_obj){
                    solution->currrent_achieve_obj=fit[i];
                    //如果到达更好，更性全局最好粒子位置
                    improved=1;
                    memmove((void*)solution->gbest, (void*)pos[i], sizeof(double)*setting->dim);
                }
            }
        }
        if(setting->print_every&&step%10000==0)
            printf("Step %d  (w=%.2f) ::min achieve_obj=%.5e\n",step,weight_inertia,solution->currrent_achieve_obj);
    }
    free_matrix(pos, setting);
    free_matrix(vel, setting);
    free_matrix(pos_b, setting);
    free_matrix(pos_nb, setting);
    free(comm_net);
    free(fit);
    free(fit_b);
    
}
