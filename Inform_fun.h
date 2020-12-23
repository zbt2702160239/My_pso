//
//  Inform_fun.h
//  My_PSO_Project
//
//  Created by mac on 2020/12/16.
//

#ifndef Inform_fun_h
#define Inform_fun_h

#include <stdio.h>
#include "Setting.h"
#include "Result.h"
void init_random_neighbor(int *comm_net,setting *setting);
void init_ring_neighbor(int *comm_net,setting *setting);
void inform(int *comm_net,double **pos_nb,double **pos_b,double *fit_b,setting *setting,result *solution);
void toast_neighbor_global(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution);
void toast_neighbor_ring(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution);
void toast_neighbor_random(int *comm_net,double **pos_nb,double **pos_b,double *fit,setting *setting,result *solution,int improved);
#endif /* Inform_fun_h */
