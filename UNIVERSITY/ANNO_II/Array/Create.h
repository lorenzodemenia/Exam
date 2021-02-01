//
// Created by demen on 30/01/2021.
//

#ifndef EX_EXAM_CREATE_H
#define EX_EXAM_CREATE_H

#endif //EX_EXAM_CREATE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * Create a normal integer array with dimension dim and all the objects are number that start in start and finish whit finish
 * @param dim
 * @param start
 * @param finish
 * @return count
 */
int create_normal_int_array(int start,int finish,int arr[]);
/**
 * Create a normal char array with dimension dim and all the objects are number that start in start and finish whit finish
 * @param dim
 * @param start
 * @param finish
 * @return count
 */
int create_normal_char_array(char start,char finish,char arr[]);
/**
 * Create a integer  two-dimensional array in dynamic memory
 * @param elem is the element that you append inside
 * @param rows number of rows
 * @param columns number of columns
 * @return the array
 */
int** create_two_dimensional_int_array(int elem,int rows,int columns);
/**
* Create a char  two-dimensional array in dynamic memory
* @param elem is the element that you append inside
* @param rows number of rows
* @param columns number of columns
* @return the array
*/
char** create_two_dimensional_char_array(char elem,int rows,int columns);
/**
 * print the integer  two-dimensional array given
 * @param arr_dim
 * @param rows
 * @param columns
 */
void print_two_int_dimensional(int **arr_dim,int rows,int columns);
/**
* print the char two-dimensional array given
* @param arr_dim
* @param rows
* @param columns
*/
void print_two_char_dimensional(char **arr_dim,int rows,int columns);
/**
 * Create a particular two-dimensional char array
 * @param dim
 * @return
 */
char** create_char_two_dimensional_strange(int dim);
/**
 * Print a particular two-dimensional char array
 * @param arr
 * @param dim
 */
void print_array_strange(char **arr,int dim);