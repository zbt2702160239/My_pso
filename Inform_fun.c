//
//  Inform_fun.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/16.
//
#include<stdlib.h>
#include<string.h>
#include "Inform_fun.h"
#include "Setting.h"
#include "Matrix_operating.h"
#include "Result.h"
void init_random_neighbor(int *comm_net,setting *setting){//初始化随机邻居
    for(int i=0;i<setting->swarm_size;i++){
        //设自己可以获得自己的通知
        comm_net[i*setting->swarm_size+i]=1;
        for(int k=0;k<setting->neighborhood_size;k++){
            int j=RANDOM_UNIFORM_INT(setting->swarm_size);
            comm_net[i*setting->swarm_size+j]=1;
        }
    }
}
void init_ring_neighbor(int *comm_net,setting *setting){
    for(int i=0;i<setting->swarm_size;i++){
        comm_net[i*setting->swarm_size+i]=1;//与自己通信
        if(i==0){//环形开始
            comm_net[i*setting->swarm_size+i+1]=1;//起点的下一个结点
            comm_net[(i+1)*setting->swarm_size+i-1]=1;//回连到尾部
        }else if(i==setting->swarm_size-1){//环形回到起点
            comm_net[i*setting->swarm_size+i-1]=1;//自己的前一个结点
            comm_net[(i-1)*setting->swarm_size+i]=1;//回到开头结点，，，，，，，可能出问题
        }else{//圆环当前点的前后结点
            comm_net[i*setting->swarm_size+i+1]=1;//自己前一个结点
            comm_net[i*setting->swarm_size+i-1]=1;//自己的后一个结点
        }
    }
}
void inform(int *comm_net,double **pos_nb,double **pos_b,double *fit_b,setting *setting,result *solution){
    for(int i=0;i<setting->swarm_size;i++){
        int best_neighbor=i;
        for(int j=0;j<setting->swarm_size;j++){//在邻居中找到最好的
            if(comm_net[i*setting->swarm_size+j]&&fit_b[j]<fit_b[best_neighbor])
                best_neighbor=j;//判断相邻结点适应性最好的结点
        }
        memmove((void*)pos_nb[i],(void*)pos_b[best_neighbor],sizeof(double)*setting->dim);//把最好的邻居位置记录下来
    }
}

void toast_neighbor_global(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution){
    
    for(int i=0;i<setting->swarm_size;i++){
        memmove((void*)pos_nb, (void*)solution->gbest, sizeof(double)*setting->dim);//周知全局最优解
    }
    
}

void toast_neighbor_ring(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution){
    inform(comm_net, pos_nb, pos_b, fit,setting,solution);
}

void toast_neighbor_random(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution,int improved){
    if(!improved)//如果没有提升从新生成邻居
    {init_random_neighbor(comm_net, setting);
        printf("update neighbor");
    }
    inform(comm_net, pos_nb, pos_b, fit,setting,solution);
}
