/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 24 Eylül 2013 Salı, 13:35
 */

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/*
 * 
 */

void matris_olustur_dinamik(int ***dizi,int satir,int sutun){
    int i,j;
    *dizi=(int**)malloc(satir*sizeof(int*));
    /*   for(i=0; i<satir; i++) 
         (*dizi)[i]=(int*)malloc(sutun*sizeof(int));
    
  
    for(i=0; i<satir; i++)
        for(j=0; j<sutun; j++)
           (*dizi)[i][j]=rand()%10; 
      */
    
    for(i=0; i<satir; i++){
        *(*dizi+i)= (int*)malloc(sutun*sizeof(int));
        for(j=0; j<sutun; j++)
            *(*(*dizi+i)+j)= rand()%10;
    }
}

void matris_degistir(int **dizi, int satir, int sutun){
    int i,j;
    for(i=0; i<satir; i++)
        for(j=0; j<sutun; j++)
            *(*(dizi+i)+j)=rand()%2;
}


void matris_yaz_dinamik(int **dizi,int satir,int sutun){
    int i,j;
    for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++) printf("%4d ",*(*(dizi+i)+j));
        printf("\n");
    }
}

void matris_carpimi_dinamik(int **A,int A_satir, int A_sutun,
                           int **B, int B_satir, int B_sutun,
                           int **C, int C_satir, int C_sutun){
    
    
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


struct tek_boyutlu_dizi {
    int eleman_sayisi;
    int *dizi_basi;
};

void tek_boyutlu_dizi_olustur(struct tek_boyutlu_dizi *tek, int eleman_sayisi){
    int i;
    tek->dizi_basi = (int*)malloc(sizeof(int)*eleman_sayisi);
    tek->eleman_sayisi= eleman_sayisi;
    for(i=0; i<eleman_sayisi; i++){
        tek->dizi_basi[i]= rand()%10;
    }
}

void print_tek_boyutlu_dizi(struct tek_boyutlu_dizi *tek){
    int i;
    for(i=0; i<tek->eleman_sayisi; i++){
         printf("%4d ", tek->dizi_basi[i]);
    }
    printf("\n");
}
int main(int argc, char** argv) {
    int **A,**B,**C;
    struct tek_boyutlu_dizi x;
    srand(time(NULL)); // rastgele (random) sayilar olusturmak icin
    matris_olustur_dinamik(&A,5,6);
    matris_olustur_dinamik(&B,6,7);
    matris_olustur_dinamik(&C,5,7);
    matris_degistir(A,5,6);
    matris_degistir(B,6,7);
    matris_degistir(C,5,7);
    printf("--- A matrisi ----\n");
    matris_yaz_dinamik(A,5,6);
    printf("--- B matrisi ----\n");
    matris_yaz_dinamik(B,6,7);
    printf("--- C matrisi ----\n");
    matris_yaz_dinamik(C,5,7);
    matris_carpimi_dinamik(A,5,6,B,6,7,C,5,7);
    printf("---- C=A*B matrisi ----\n");
    matris_yaz_dinamik(C,5,7);
   printf("-----------------------\n");
   tek_boyutlu_dizi_olustur(&x,20);
   print_tek_boyutlu_dizi(&x);
    return (EXIT_SUCCESS);
}

