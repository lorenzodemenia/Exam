//
// Created by demen on 29/01/2021.
//
#include "function_char.h"
#include<time.h>
#include <stdlib.h>
list_c insert_letters(){
    list_c  listC=(list_c)malloc(sizeof(struct list_char));
    listC=NULL;
    srand(time(NULL));
    for (int i = 0; i < 9; ++i) {
        int dim=rand()%2;
        if(dim==1){
            int rnd_up=rand()%26;
            char elem='A'+rnd_up;
            append_char(elem,&listC);
        } else{
            int rnd_down=rand()%26;
            char elem_2='a'+rnd_down;
            append_char(elem_2,&listC);
        }
    }
    return listC;
}
void uppercase(list_c listC){
    while(listC){
        if(listC->info>='a' && listC->info<='z'){
            listC->info=listC->info-32;
        }
        listC=listC->next;
    }
}
void lowercase(list_c listC){
    while(listC){
        if(listC->info>='A' && listC->info<='Z'){
            listC->info=listC->info+32;
        }
        listC=listC->next;
    }
}
int count_all_occurrences(list_c listC,char elem){
    int count=0;

    while(listC){
        if(listC->info==elem){
            count++;
        }
        listC=listC->next;
    }

    return count;
}
int IsPresent(list_c listC,char elem){
    if(listC){
        return elem==listC->info||IsPresent(listC->next,elem);
    }
    return 0;
}
int count_last_position(list_c listC,char elem){
    int count=0;

    while (listC){
        if(IsPresent(listC,elem)==0){
            return count;
        } else{
            count++;
        }
        listC=listC->next;
    }
    return 0;
}

list_c occurrences_elem_times(list_c listC,char elem,int dim,int *count){
    list_c listC1;
    listC1=(list_c)malloc(sizeof(struct list_char));
    listC1=NULL;
    int c=0;
    list_c copy=listC;
    while(c<dim) {
        while (listC && c<dim) {
            append_char(listC->info, &listC1);
            listC = listC->next;
            c++;
        }
        listC=copy;
    }
    *count=count_all_occurrences(listC1,elem);
    return listC1;
}

int sorted_char_list(list_c l){
    if(!l || !l->next){ // si controlla prima se la lista è vuota perché se no avremo un problema di Stackoverflow siccome andiamo a controllare uno spazio inesistente
        return 1;       // abbiamo una cortocircuitazione forzata della funzione buleana
    }else{
        return (l->info<l->next->info)&&sorted_char_list(l->next); //controlla se la lista è ordinata ricorsivamente e anche qui abbiamo la stessa cosa ma non andrebbe
                                                                  // in overflow ma avremo una perdita di efficenza
    }
}
int sorted_list_it_char(list_c l){
    if(!l || !l->next){
        return 1;
    } else{
        while (l){
            if(l->info>l->next->info){
                return 1;
            }
            l=l->next;
        }
        return 0;

    }
}

void bubble_sort_char(list_c *listC){
    list_c list;
    list_c lptr=NULL;
    int swapped;
    if(listC==NULL){
        return;
    }
    do {
        swapped=0;
        list=*listC;
        while (list->next!=lptr){
            if(list->info>list->next->info){
                char tmp=list->info;
                list->info=list->next->info;
                list->next->info=tmp;
                swapped=1;
            }
            list=list->next;
        }
        lptr=list;
    }while (swapped);
    *listC=list;
}

