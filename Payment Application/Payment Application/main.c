//
//  main.c
//  Payment Application
//
//  Created by Ahmed Abdelwahab on 12/21/22.
//

#include <stdio.h>
#include <stdbool.h>
#include "modules/test/test.h"
#include "modules/application/application.h"

int looping_condition;


int main(int argc, const char * argv[]) {
    do
    {
        appStart();
        printf("enter an number to continue : (0 to stop) :");
        scanf("%d",&looping_condition);
        while (getchar() != '\n');
    }while(looping_condition!=0);
    
    return 0;
}
