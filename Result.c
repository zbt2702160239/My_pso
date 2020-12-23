//
//  Result.c
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//
#include <stdlib.h>
#include "Result.h"
#include "Setting.h"
result *result_init(setting *setting){
    result *myresult=(result*)malloc(sizeof(result));
    myresult->gbest=(double*)malloc(setting->dim*sizeof(double));
    return myresult;
}
void free_result(result *myresult){
    free(myresult->gbest);
    free(myresult);
}
