//
//  main.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#include <stdio.h>
#include "Pso_Algorithm.h"
#include "Setting.h"
#include "Result.h"
#include "CalcParam.h"
int main(int argc, const char * argv[]) {
    int eval_fun_select;
    int neighborhood_strategy;
    eval_fun e_f= NULL;
    setting *my_setting=NULL;
    result *my_result=NULL;
    while(1){
    printf("Please select evaluation function 1 represent rosenbrock ,2 represent griewank,3 represent shphere");
    scanf("%d",&eval_fun_select);
    printf("Please select neighborhood strategy 0 represent random ,1 represent ring,2 represent global");
    scanf("%d",&neighborhood_strategy);
        
        switch(eval_fun_select){
            case 1: e_f=calc_adaptation_rosenbrock;
                my_setting=setting_param(30, -2.048, 2.048,neighborhood_strategy);
                my_result=result_init(my_setting);
                break;
            case 2: e_f=calc_adaptation_griewank;
                my_setting=setting_param(30, -600, 600,neighborhood_strategy);
                my_result=result_init(my_setting);
                break;
            case 3: e_f=calc_adaptation;
                my_setting=setting_param(30, -100, 100,neighborhood_strategy);
                my_result=result_init(my_setting);
                break;
            case 4:e_f=calc_adaption_rastrigin;
                my_setting=setting_param(30, 100, -100, neighborhood_strategy);
                break;
            default:e_f=calc_adaptation;
                my_setting=setting_param(30, -100, 100,neighborhood_strategy);
                my_result=result_init(my_setting);
                break;
        }
        
    pso_algorithm(e_f,my_setting, my_result);
    printf("\n");
    }
}
