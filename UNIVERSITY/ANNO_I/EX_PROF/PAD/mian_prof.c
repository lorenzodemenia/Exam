//
// Created by demen on 30/01/2021.
//
#include <stdio.h>
#include "pad.h"

int main() {
    char pad[10];
    char seq[1024];

    scanf("%s", pad);
    scanf("%s", seq);

    printf("%d\n",entryTime(seq, pad));
    return 0;
}