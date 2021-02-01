//
// Created by demen on 29/01/2021.
//
#include "function_char.h"

void append_int(int elem,list_i *arr){
    list_i tlist;
    tlist=(list_i)malloc(sizeof(struct list_int));


    tlist->info=elem;
    tlist->next=NULL;

    if(*arr==NULL){
        *arr=tlist;
    } else{
        list_i list=*arr;
        while (list->next){
            list=list->next;
        }
        list->next=tlist;

    }
}
int prepend_int(list_i *listC,int elem){ //si utilizza * davanti al parametro per permettere alla funzione di modificare la lista
                                         //altrimenti se volessimo solo leggere non dobbiamo mettere * nella funzione e & nel parametro della chiamata alla funzione
    list_i list;
    list=(list_i)malloc(sizeof(struct list_int));
    if(list){
        list->info=elem;
        list->next=*listC;
        *listC=list;
        return 1;
    } else{
        return 0;
    }

    return 1;
}
int prepend_char(list_c *listC,char elem){
    list_c list;
    list=(list_c)malloc(sizeof(struct list_char));
    if(list){
        list->info=elem;
        list->next=*listC;
        *listC=list;
        return 1;
    } else{
        return 0;
    }
}
void append_char(char elem,list_c *arr){
    list_c tlist;
    tlist=(list_c)malloc(sizeof(struct list_char));


    tlist->info=elem;
    tlist->next=NULL;

    if(*arr==NULL){
        *arr=tlist;
    } else{
        list_c list=*arr;
        while (list->next){
            list=list->next;
        }
        list->next=tlist;

    }
}

list_i create_int(){
    list_i tlist;
    tlist=(list_i)malloc(sizeof(struct list_int));
    tlist=NULL;
    int i=9;
    while (i>=0){
        append_int(i,&tlist);
        i--;
    }

    return tlist;
}




list_c create_char(){
    list_c tlist;
    tlist=(list_c)malloc(sizeof(struct list_char));
    tlist=NULL;
    return tlist;
}

void print_int(list_i list){
    while (list){
        printf("%d\n",list->info);
        list=list->next;
    }
}

void print_char(list_c list){
    while (list){
        printf("%c\n",list->info);
        list=list->next;
    }
}

void Free_int(list_i list){
    if(list){
        Free_int(list->next);
    }
    free(list);
}


void Free_char(list_c list){
    if(list){
        Free_char(list->next);
    }
    free(list);
}

void print_all(list_c listC,list_i listI){
    while (listI || listC){
        printf("%d  %c\n",listI->info,listC->info);
        listC=listC->next;
        listI=listI->next;
    }
}

int random_number(int dim){
    srand(time(NULL));
    return  rand()%dim;
}
void print_back_char(list_c listC){// se volessimo in una ricorsione lavorare con la lista al contrario dobbiamo trattare
    // l'elemento corrente dopo quelli dopo lo scrorrimento della lista sugli elementi della fine , quindi nella ricorsione
    if(listC){
        print_back_char(listC->next);//scorrimento ricorsivo della lista al contrario
        printf("%c ",listC->info);//trattamento dell'elemento
    }
}
void print_back_int(list_i listI){// se volessimo in una ricorsione lavorare con la lista al contrario dobbiamo trattare
    // l'elemento corrente dopo quelli dopo lo scrorrimento della lista sugli elementi della fine , quindi nella ricorsione
    if(listI){
        print_back_int(listI->next);//scorrimento ricorsivo della lista al contrario
        printf("%d ",listI->info);//trattamento dell'elemento
    }
}