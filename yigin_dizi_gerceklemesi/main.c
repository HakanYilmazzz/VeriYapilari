/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 28 Ekim 2013 Pazartesi, 09:19
 */

/** yigin veri yapisinin dizilerle gerceklenmesi*/

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#define SENTINEL -1000000

struct yigin{
    int *dizi;
    int ust;
    int kapasite;
};

struct yigin* yigin_olustur(int kapasite){
    struct yigin* ptr=(struct yigin *)malloc(sizeof(struct yigin));
    ptr->dizi=(int *)malloc(sizeof(int)*kapasite);
    ptr->ust=-1;
    ptr->kapasite=kapasite;
    return ptr;
}

int yigin_dolumu(struct yigin *ptr){
    if(ptr->ust==ptr->kapasite-1) return 1;
    else return 0;
}

void yigin_ekle(struct yigin *ptr,int eleman){
    if(yigin_dolumu(ptr)) return;
    ptr->ust++;
    ptr->dizi[ptr->ust]=eleman;
}

void yigin_yok_et(struct yigin** ptr){
 free((*ptr)->dizi);
 free(*ptr);
 *ptr=NULL;
}
struct yigin* kapasiteyi_iki_kat_yap(struct yigin* ptr){
    struct yigin* ptr_yeni;
    int i;
    ptr_yeni=yigin_olustur(2*ptr->kapasite);
    for(i=0; i<=ptr->ust; i++) ptr_yeni->dizi[i]=ptr->dizi[i];
    ptr_yeni->ust=ptr->ust;
    yigin_yok_et(&ptr);
    return ptr_yeni;
}
void yigin_yaz(struct yigin* ptr){
    int i;
    printf("Yigin Kapasitesi: %4d\n",ptr->kapasite);
    printf("Yigindaki Eleman Sayisi: %4d\n",ptr->ust+1);
    printf("Yigindaki elemanlar:\n");
    for(i=ptr->ust; i>=0; i--) printf("%5d ",ptr->dizi[i]);
    printf("\n");
}

int yigin_bosmu(struct yigin* ptr){
    if(ptr->ust==-1) return 1;
    return 0;
}

int yigin_eleman_sil(struct yigin *ptr){
    if(yigin_bosmu(ptr)) return SENTINEL;
    ptr->ust--;
    return ptr->dizi[ptr->ust+1];
}

int main(int argc, char** argv) {
    struct yigin *yigin_ptr;
    yigin_ptr=yigin_olustur(10);
    yigin_ekle(yigin_ptr,-200);
    yigin_ekle(yigin_ptr,200);
    yigin_ekle(yigin_ptr,500);
    yigin_ekle(yigin_ptr,400);
    yigin_yaz(yigin_ptr);
    yigin_eleman_sil(yigin_ptr);
    yigin_eleman_sil(yigin_ptr);
    yigin_ekle(yigin_ptr,1500);
    yigin_yaz(yigin_ptr);
    
    yigin_ptr=kapasiteyi_iki_kat_yap(yigin_ptr);
    yigin_yaz(yigin_ptr);
  //  yigin_yok_et(&yigin_ptr);
    return (EXIT_SUCCESS);
}

