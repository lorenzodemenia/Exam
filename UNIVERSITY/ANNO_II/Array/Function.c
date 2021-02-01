//
// Created by demen on 30/01/2021.
//
#include "Function.h"


int** extend_array_int(int **arr,int dim ,int rows,int cols){

    int **arr_dim;
    arr_dim=(int**)malloc(sizeof(int*)*dim);

    for (int i = 0; i <dim ; ++i) {
        arr_dim[i]=(int*)malloc(sizeof(int)*dim);
    }

    for (int i = 0,l=0; i <dim; ++i,++l) {
        if(l==rows){
            l=0;
        }
        for (int j = 0,k=0; j < dim ; ++j,++k) {
            if(k==cols){
                k=0;
            }
            arr_dim[i][j]=arr[l][k];
        }
    }

    return arr_dim;
}
char**  extend_array_char(char **arr,int dim ,int rows,int cols){
    char **arr_dim;
    arr_dim=(char**)malloc(sizeof(char*)*dim);
    for (int i = 0; i <dim ; ++i) {
        arr_dim[i]=(char *)malloc(sizeof(char )*dim);
    }
    for (int i = 0,l=0; i <dim; ++i,++l) {
        if(l==rows){
            l=0;
        }
        for (int j = 0,k=0; j < dim ; ++j,++k) {
            if(k==cols){
                k=0;
            }
            arr_dim[i][j]=arr[l][k];
        }
    }

    return arr_dim;

}

int number_of_times(char **arr,char elem ,int rows,int cols){
    int count=0;

    for (int i = 0; i < rows ; ++i) {
        for (int j = 0; j < cols ; ++j) {
            if(elem==arr[i][j]){
                count++;
            }
        }
    }
    return count;
}
char** find_same(char **counters,int dim,int *count){
    char **bubble;
    bubble=(char**)malloc(sizeof(char*)*dim);
    bubble[0]=counters[0];
    int dim_bubble=0,m=1;
    for (int i = 0; i < dim ; ++i) {
        for (int j = 0; j <dim_bubble ; ++j) {
            if(counters[i]==bubble[j]){
                m=0;
            }
        }
        if(m==1){
            dim_bubble++;
            bubble[dim_bubble]=counters[i];
        }
        m=1;
    }
    *count=dim_bubble;
    return bubble;

}
char** bubble_sort_adapt(char **counters, int count_dim,int *count){
    int dim_bubble=0;
    char **bubble=find_same(counters,count_dim,&dim_bubble);
    char *a;

    for (int i = 0; i <dim_bubble; ++i) {
        for (int j = i+1; j <dim_bubble-1; ++j) {
            if(strcmp(bubble[i],bubble[j])>0){
                a=bubble[i];
                bubble[i]=bubble[j];
                bubble[j]=a;
            }
        }

    }


    *count=dim_bubble;

    return bubble;
}


