//
// Created by demen on 30/01/2021.
//

#include "pad.h"

struct pos{
    int r;
    int c;
};

typedef struct pos tpos;

int entryTime(char* s, char* keypad) {
    tpos vect[9];
    int i;
    int time = 0;
    for (i=0; keypad[i]!='\0'; i++) {
        vect[keypad[i]-'1'].r=i/3;
        vect[keypad[i]-'1'].c=i%3;
    }

    for (i=0; s[i]!='\0'; i++)
        if (s[i+1]!='\0') {
            int distr;
            int distc;
            distr = abs(vect[s[i]-'1'].r-vect[s[i+1]-'1'].r);
            distc = abs(vect[s[i]-'1'].c-vect[s[i+1]-'1'].c);

            if (distr > distc)
                time+=distr;
            else
                time+=distc;
        }
    return time;
}