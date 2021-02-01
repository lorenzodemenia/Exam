//
// Created by demen on 30/01/2021.
//
#include "function_ex1.h"
int prev, next;

int next;

int len_seq, k;



int a, b, c;

int main(){


    scanf("%d", &next);
    somma_sequenza(next);

    scanf("%d", &next);
    sequenza(next);

    scanf("%d", &len_seq);
    scanf("%d", &k);
    cerca_in_sequenza(len_seq,k);

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    minimo_c(a,b,c);

    return 0;
}
