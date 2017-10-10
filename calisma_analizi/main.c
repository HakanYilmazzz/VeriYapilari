/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 30 Eylül 2013 Pazartesi, 09:19
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

int dizi_en_buyuk(int *dizi, int N){
    int i,en_buyuk;
    en_buyuk=dizi[0];
    for(i=1; i<N; i++){
        if(dizi[i]>en_buyuk) en_buyuk=dizi[i];
    }
    return en_buyuk;
}
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

