
#include "function_char.h"

int main() {

    list_i list_int=create_int();
    list_c list_char=insert_letters();
    print_char(list_char);

    printf("Uppercase list :\n");
    uppercase(list_char);
    print_char(list_char);
    printf("lowercase list :\n");
    lowercase(list_char);
    print_char(list_char);
    printf("occurrences in the list :\n");
    print_char(list_char);
    printf("Number: %d\n",count_all_occurrences(list_char,'a'));
    printf("Is there in the list :\n");
    print_char(list_char);
    printf("there is: %d\n",count_last_position(list_char,'a'));
    list_c listC;
    listC=(list_c)malloc(sizeof(struct list_char));
    listC=NULL;
    for (int i = 0; i <4 ; ++i) {
        if(i%2==0) {
            append_char('b', &listC);
        }else{
            append_char('a', &listC);
        }
    }
    int count=0;
    list_c copy=occurrences_elem_times(listC,'a',10,&count);
    print_char(copy);
    printf("Number of times that a is in the listC of size dim: %d",count);
    printf("\nIs this list sorted?\n");
    int m=sorted_list_it_char(list_char);
    print_char(list_char);
    if(m==1){
        printf("\nYES\n");
    }else{
        printf("\nNO\n");
    }
    printf("\nBUBBLE UNSORTED FUNCTION\n");
    list_c list_sort=create_char();
    for (int i = 0; i <9 ; ++i) {
        append_char('i'-i,&list_sort);
    }
    print_char(list_sort);
    printf("\nBUBBLE SORTED FUNCTION\n");
    bubble_sort_char(&list_sort);
    print_char(list_sort);
    int sort=sorted_char_list(list_sort);
    if(sort==1){
        printf("\nYES\n");
    }else{
        printf("\nNO\n");
    }


    Free_int(list_int);
    Free_char(list_char);
    Free_char(list_sort);
    Free_char(listC);




    return 0;
}
