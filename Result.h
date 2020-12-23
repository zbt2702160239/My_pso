//
//  Result.h
//  My_PSO_Project
//
//  Created by mac on 2020/12/15.
//

#ifndef Result_h
#define Result_h

#include <stdio.h>
#include "Setting.h"
typedef struct {

    double currrent_achieve_obj;//当前所能到达的最优
    double *gbest;//全局最优解数组
}result;
result *result_init(setting *setting);
void free_result(result *myresult);
#endif /* Result_h */
