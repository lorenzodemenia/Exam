//
// Created by demen on 30/01/2021.
//

#ifndef EX_EXAM_FUNCTION_H
#define EX_EXAM_FUNCTION_H

#endif //EX_EXAM_FUNCTION_H
#include <stdlib.h>
#include <stdio.h>
#include "Create.h"

/**
 * This function extends the rows and cols of  two-dimensional integer array dim times
 * @param arr is the two-dimensional array
 * @param dim the number that you  need to extends
 * @param rows the number of rows
 * @param cols the number of cols
 */
int**  extend_array_int(int **arr,int dim ,int rows,int cols);
/**
 * This function extends the rows and cols of  two-dimensional char array dim times
 * @param arr is the two-dimensional array
 * @param dim the number that you  need to extends
 * @param rows the number of rows
 * @param cols the number of cols
 */
char**  extend_array_char(char **arr,int dim ,int rows,int cols);
/**
 * This function count how many times the element elem is in the two-dimensional dynamic array of char
 * @param arr the two-dimensional dynamic array of char
 * @param elem the element to find and count
 * @param rows the number of rows
 * @param cols the number of cols
 * @return the number of times that the element elem is in the array
 */
int number_of_times(char **arr,char elem ,int rows,int cols);

char** bubble_sort_adapt(char **counters, int count_dim,int *count);

char** find_same(char **counters,int dim,int *count);
