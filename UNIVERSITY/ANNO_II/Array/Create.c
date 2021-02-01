//
// Created by demen on 30/01/2021.
//
#include "Create.h"
#include <math.h>
int create_normal_int_array(int start,int finish,int arr[]) {
    int count=abs(finish-start)+1;
    if (start <= finish) {
        int i=0;
        while (i <= count){

            arr[i] = start + i;
            i++;

        }
    } else {
        int i=0;
        while (i <=count){
            arr[i] = start - i;
            i++;

        }
    }
    return count;
}
int create_normal_char_array(char start,char finish,char arr[]){
    int count=abs(finish-start)+1;
    if (start <= finish) {
        int i=0;
        while (i <= count){

            arr[i] = start + i;
            i++;

        }
    } else {
        int i=0;
        while (i <=count){
            arr[i] = start - i;
            i++;

        }
    }
    return count;
}
int** create_two_dimensional_int_array(int elem,int rows,int columns){
    int **arr_dim;
    arr_dim=(int**)malloc(sizeof(int*)*rows);
    for (int i = 0; i <rows ; ++i) {
        arr_dim[i]=(int*)malloc(sizeof(int)*columns);
    }
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j <columns ; ++j) {
            arr_dim[i][j]=elem;
        }
    }
    return arr_dim;
}
char** create_two_dimensional_char_array(char elem,int rows,int columns){
    char **arr_dim;
    arr_dim=(char**)malloc(sizeof(char*)*rows);
    for (int i = 0; i <rows ; ++i) {
        arr_dim[i]=(char*)malloc(sizeof(char)*columns);
    }
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j <columns ; ++j) {
            arr_dim[i][j]=elem;
        }
    }
    return arr_dim;

}
void print_two_int_dimensional(int **arr_dim,int rows,int columns){
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j <columns ; ++j) {
            printf("%d ",arr_dim[i][j]);
        }
        printf("\n");
    }
}
void print_two_char_dimensional(char **arr_dim,int rows,int columns){
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j <columns ; ++j) {
            printf("%c ",arr_dim[i][j]);
        }
        printf("\n");
    }
}

char** create_char_two_dimensional_strange(int dim){
    char **arr;
    arr=(char**)malloc(sizeof(char*)*dim);

    for (int i = 0; i <dim ; ++i) {
        arr[i]=(char*)malloc(sizeof(char));
    }

    for (int i = 0; i < dim ; ++i) {
        if(i%2==0){
            arr[i]="Omega";
        }else{
            arr[i]="Alpha";
        }
    }
    return arr;
}
void print_array_strange(char **arr,int dim){
    for (int i = 0; i < dim ; ++i) {
        printf("%s",arr[i]);
        printf("\n");

    }
}