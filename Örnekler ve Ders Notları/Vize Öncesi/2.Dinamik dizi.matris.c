#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*-------------------------------------------------------------*/
void tek_boyutlu_dizi_olustur(int **dizi, int eleman_sayisi){
        *dizi=(int*)malloc(sizeof(int)*eleman_sayisi);
        for(int i=0; i<eleman_sayisi; i++) {
                *(*dizi+i)= rand()%10;
        }
}
/*-------------------------------------------------------------*/
void tek_boyutlu_dizi_yaz(int *dizi, int eleman_sayisi){
        for(int i=0; i<eleman_sayisi; i++) {
                printf("%p     ", (dizi+i));
        }
        printf("\n");
        for(int i=0; i<eleman_sayisi; i++) {
                printf("%10d ", *(dizi+i));
        }
        printf("\n");
}
/*-------------------------------------------------------------*/
void dinamik_matris_olustur(int ***dizi,int satir,int sutun){
        *dizi=(int**)malloc(sizeof(int*)*satir);
        for(int i=0; i<satir; i++) {
                *(*dizi+i)= (int*)malloc(sizeof(int)*sutun);
                for(int j=0; j<sutun; j++)
                        *(*(*dizi+i)+j)= rand()%3;
        }
}
/*-------------------------------------------------------------*/
void dinamik_matris_yaz(int **dizi,int satir,int sutun){
        for(int i=0; i<satir; i++) {
                for(int j=0; j<sutun; j++)
                printf("%4d ",*(*(dizi+i)+j));
            printf("\n");
        }
}
/*-------------------------------------------------------------*/
void matris_degistir(int **dizi, int satir, int sutun){
        for(int i=0; i<satir; i++)
                for(int j=0; j<sutun; j++)
                        *(*(dizi+i)+j)=rand()%2;
}
/*-------------------------------------------------------------*/
void dinamik_matris_carpimi(int **A,int A_satir, int A_sutun,
                            int **B, int B_satir, int B_sutun,
                            int **C, int C_satir, int C_sutun){
                            
        if(A_sutun!=B_satir) {
                printf("Carpim matrislerinin boyutlari uyusmuyor!!!");
                return;
        }
        
        else if(A_satir!=C_satir || B_sutun!=C_sutun) {
                printf("Sonuc matrisinin boyutlari carpan matrislere uymuyor!!!\n");
                return;
        }
        
        else{
                for(int i=0; i<A_satir; i++)
                        for(int j=0; j<B_sutun; j++) {
                                C[i][j]=0;
                                for(int k=0; k<A_sutun; k++)
                                        C[i][j]=C[i][j]+A[i][k]*B[k][j];
                        }
        }
        
}


int main(){

        int **A,**B,**C;
        int *dizi;
        int eleman_sayisi = 10;
        srand(time(NULL));

//        tek_boyutlu_dizi_olustur(&dizi, eleman_sayisi);
//        tek_boyutlu_dizi_yaz(dizi, eleman_sayisi);

        dinamik_matris_olustur(&A,4,3);
        printf("--- A matrisi ----\n");
        dinamik_matris_yaz(A,4,3);

        A[0][1]=100;
        printf("--- A matrisi ----\n");
        dinamik_matris_yaz(A,4,3); // değiştirme işlemi

        dinamik_matris_olustur(&B,3,5);
        printf("--- B matrisi ----\n");
        dinamik_matris_yaz(B,3,5);

        dinamik_matris_olustur(&C,4,5);
        printf("--- C matrisi ----\n");
        dinamik_matris_yaz(C,4,5);


        dinamik_matris_carpimi(A,4,3,B,3,5,C,4,5);
        printf("---- C=A*B matrisi ----\n");
        dinamik_matris_yaz(C,4,5);
        printf("-----------------------\n"); //Matris Çarpımı


        return (EXIT_SUCCESS);

}
