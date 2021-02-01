//
// Created by demen on 29/01/2021.
//

#ifndef EX_EXAM_FUNCTION_H
#define EX_EXAM_FUNCTION_H

#endif //EX_EXAM_FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct list_int {
    int info;
    struct list_int *next;
};
struct list_char{
    char info;
    struct list_char *next;
};
typedef struct list_char *list_c;
typedef struct list_int *list_i;
/**
 * This function append an element (in this case is a integer element) at the end of the list
 * @param elem a integer element
 * @param arr the list
 */
void append_int(int elem,list_i *arr);
/**
 * This function append an element (in this case is a char element) at the end of the list
 * @param elem a char element
 * @param arr the list
 */
void append_char(char elem,list_c *arr);
/**
 * This function prepend an element (in this case is a integer element) at the head of the list
 * @param elem a integer element
 * @param arr the list
 */
int prepend_int(list_i *listC,int elem);
/**
* This function prepend an element (in this case  is a char element) at the head of the list
* @param elem a integer element
* @param arr the list
*/
int prepend_char(list_c *listC,char elem);
/**
 * Create a char list
 * @return the created list
 */
list_i create_int();
/**
 * Create an int list
 * @return the created list
 */
list_c create_char();
/**
 * Print the char list
 * @param list
 */
void print_int(list_i list);
/**
 * Print the Int list
 * @param list
 */
void print_char(list_c list);
/**
 * It Destroy the given int list
 * @param list
 */
void Free_int(list_i list);
/**
 * It Destroy the given char list
 * @param list
 */
void Free_char(list_c list);
/**
 * Print both of the list that I give them
 * @param listC
 * @param listI
 */
void print_all(list_c listC,list_i listI);
/**
 * Create a random number between 0 and dim
 * @param dim
 * @return
 */
int random_number(int dim);
/**
 * Print the char  list in reverse mode Recursively
 * @param listC
 */
void print_back_char(list_c listC);
/**
 * Print the int list in reverse mode Recursively
 * @param listC
 */
void print_back_int(list_i listI);