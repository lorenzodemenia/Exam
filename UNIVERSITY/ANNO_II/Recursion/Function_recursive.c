//
// Created by demen on 01/02/2021.
//
#include "Function_recursive.h"

int roma(int m,int n){
    if(m==0 || n==0){
        return 1;
    } else{
        return roma(m-1,n)+roma(m,n-1);
    }
}