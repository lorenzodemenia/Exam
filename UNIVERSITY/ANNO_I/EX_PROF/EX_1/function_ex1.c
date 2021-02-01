//
// Created by demen on 30/01/2021.
//
#include "function_ex1.h"
int somma = 0;
int letti = 0;
int is_present = 0;
int minimo, massimo;
float media;
int sum = 0;
int prev;
int all_even = 1,n,i;
void somma_sequenza(int next){

    if (next % 2 != 0)
        sum = next;

    do {
        prev = next;
        scanf("%d", &next);
        if (next % 2 != 0)
            sum = sum + next;
    } while (prev + 1 != next);

    printf("%d\n", sum);
}
void sequenza(int next){
    do {
        prev = next;
        if (prev % 2 == 0)
            all_even = 0;
        scanf("%d", &next);
    } while (prev || next);

    if (all_even)
        printf("SI\n");
    else
        printf("NO\n");
}
void cerca_in_sequenza(int len_seq,int k){
    for (i = 0; i < len_seq; ++i) {
        scanf("%d", &n);
        if (n==k)
            is_present = 1;
    }

    if (is_present)
        printf("SI\n");
    else
        printf("NO\n");
}
void minimo_c(int a,int c,int b){
    minimo = a;
    massimo = a;
    somma = somma + a;
    letti = letti + 1;


    if (b < minimo)  minimo  = b;
    if (b > massimo) massimo = b;
    somma = somma + b;
    letti = letti + 1;


    if (c < minimo)  minimo  = c;
    if (c > massimo) massimo = c;
    somma = somma + c;
    letti = letti + 1;

    while (a != b || b != c) {
        a = b;
        b = c;
        scanf("%d", &c);
        if (c < minimo)  minimo  = c;
        if (c > massimo) massimo = c;
        somma = somma + c;
        letti = letti + 1;
    }

    media = (somma - 2*c)*1.0 / (letti - 2);

    /*output: non cambiare*/
    printf("%d\n", minimo);
    printf("%d\n", massimo);
    printf("%.3f", media); /*specifica che vogliamo 3 decimali dopo la vigola*/
}