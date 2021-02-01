//
// Created by demen on 29/01/2021.
//

#ifndef EX_EXAM_FUNCTION_CHAR_H
#define EX_EXAM_FUNCTION_CHAR_H

#endif //EX_EXAM_FUNCTION_CHAR_H

#include "function_create.h"

/**
 * This function  append and create a uppercase and lowercase's list
 * @param listC
 */
list_c insert_letters();
/**
 * Change all the lowercase letters in uppercase
 * @param listC
 */
void uppercase(list_c listC);
/**
 * Change all the uppercase letters in lowercase
 * @param listC
 */
void lowercase(list_c listC);
/**
 * Count and return all the occurrences of elem in the list
 * @param listC
 * @param elem
 * @return count
 */
int count_all_occurrences(list_c listC,char elem);

/**
 * Check if elem there is or not in the list
 * @param listC
 * @param elem
 * @return
 */
int IsPresent(list_c listC,char elem);
/**
 * Return the last position of elem in the list
 * @param listC
 * @param elem
 * @return last
 */
int count_last_position(list_c listC,char elem);

/**
 * extends the list dim times for searching how many times elem is in the list long dim
 * @param listC
 * @param elem
 * @param dim
 * @param count
 * @return list_c list
 */
list_c occurrences_elem_times(list_c listC,char elem,int dim,int *count);
/**
 * this function cech recursively if the list is sorted
 * @param l
 * @return 0 if is sorted 1 if it isn't
 */
int sorted_char_list(list_c l);
/**
 * this function cech iteratively if the list is sorted
 * @param l
 * @return 0 if is sorted 1 if it isn't
 */
int sorted_list_it_char(list_c l);
/**
 * this function sort the char list
 * @param listC
 */
void bubble_sort_char(list_c *listC);
