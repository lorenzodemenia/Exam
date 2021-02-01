//
// Created by demen on 29/01/2021.
//
#include "Function.h"





int main(){
    int arr[1000];
    char arr_char[1000];

    printf("INT ARRAY\n");
    int count=create_normal_int_array(1,10,arr);
    for (int i = 0; i < count; ++i) {
        printf("%d ",arr[i]);
    }

    printf("\n");
    printf("CHAR ARRAY\n");
    int count_char=create_normal_char_array('a','l',arr_char);
    for (int i = 0; i < count_char; ++i) {
        printf("%c ",arr_char[i]);
    }
    printf("\n");
    printf("DYNAMIC INT ARRAY\n");
    int **arr_dim_int=create_two_dimensional_int_array(4,3,4);
    print_two_int_dimensional(arr_dim_int,3,4);

    printf("\n");
    printf("DYNAMIC CHAR ARRAY \n");
    char **arr_dim_char= create_two_dimensional_char_array('a',3,4);
    print_two_char_dimensional(arr_dim_char,3,4);

    printf("\n");
    printf("DYNAMIC INT ARRAY AUGMENTED \n");
    int **arr_ex_int=extend_array_int(arr_dim_int,10,3,4);
    print_two_int_dimensional(arr_ex_int,10,10);

    printf("\n");
    printf("DYNAMIC CHAR ARRAY AUGMENTED \n");
    char **arr_ex_char=extend_array_char(arr_dim_char,10,3,4);
    print_two_char_dimensional(arr_ex_char,10,10);

    printf("\n");
    printf("DYNAMIC INT COUNT ELEMENT IN ARRAY \n");
    int count_int=number_of_times(arr_ex_char,'a',10,10);
    printf("%d ",count_int);

    printf("\n");
    printf("DYNAMIC CHAR BUBBLE NOT SORT ARRAY \n");
    char **arr_bubble=create_char_two_dimensional_strange(20);
    int dim=0;
    char **bubble=bubble_sort_adapt(arr_bubble,20,&dim);
    print_array_strange(arr_bubble,20);
    printf("DYNAMIC CHAR BUBBLE  SORT ARRAY \n");
    print_array_strange(bubble,dim);
    printf("MAGGIORE DI:%d",strcmp("Omega","Alpha"));



    return 0;
}

