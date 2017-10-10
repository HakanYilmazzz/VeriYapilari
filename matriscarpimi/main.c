/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 24 Eylül 2013 Salı, 13:00
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
void matris_carpimi(int A[][3], int A_satir, int A_sutun,
                    int B[][2], int B_satir,int B_sutun,
                    int C[][2],int C_satir, int C_sutun){
    int i,j,k;
    if(A_sutun!=B_satir){
        printf("Carpim matrislerinin boyutlari uyusmuyor!!!");
        return;
    }
    else if(A_satir!=C_satir || B_sutun!=C_sutun){
        printf("Sonuc matrisinin boyutlari carpan matrislere uymuyor!!!\n");
        return;
    }
    else{
        for(i=0; i<A_satir; i++)
            for(j=0; j<B_sutun; j++){
                C[i][j]=0;
                for(k=0; k<A_sutun; k++)
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
            }   
    }
}

void matris_yaz(int (*A)[2], int satir){
    int i,j;
    for(i=0; i<satir; i++){
        for(j=0; j<2; j++) printf("%6d ",A[i][j]);
        printf("\n");
    }
}



void foo2(int (*dizi)[3]){
    printf("%6d\n",(*(dizi+1))[0]);
    printf("%6d\n",(dizi+1)[2][2]);
    printf("%6d\n",(*dizi)[1]);
    printf("%6d\n",dizi[0][1]);
    printf("%6d\n",(*dizi)[2]);
    printf("%10p\n",dizi);
    printf("%10p\n",*dizi);
    printf("%10p\n",dizi+1);
    printf("%10p\n",*(dizi+1));
    printf("%10p\n",dizi+2);
    
}



int main(int argc, char** argv) {
    int A[][3]={{198,450,2},{92,111,444},{5,-6,89},{-889,200,359}};
    int B[][2]={{0,1},{2,4},{3,1}};
    int C[4][2];
    
    
    int dizi0[3]={0,1,2};
    int dizi1[3]={4,5,6};
    int dizi2[3]={8,9,10};
    
    printf("---%10p----\n",A);
    printf("---%10p----\n",*A);
    printf("---%10d----\n",**A);
    foo2(A);
    
    
  
    
   matris_carpimi(A,4,3,B,3,2,C,4,2);
    
   matris_yaz(C,4);
  
   
    return (EXIT_SUCCESS);
}

