/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 07 Ekim 2013 Pazartesi, 09:29
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

struct eleman{
    int icerik;
    struct eleman *ileri;
};

typedef struct eleman Eleman;

typedef Eleman* Elemanptr;

Elemanptr yeni_eleman(int icerik){
    Elemanptr eleman;
    eleman =(Elemanptr)malloc(sizeof(Eleman));
    eleman->icerik=icerik;
    eleman->ileri=NULL;
    return eleman;
}

struct liste{
    Elemanptr bas;
    Elemanptr son;
};

typedef struct liste Liste;
typedef Liste* Listeptr;

Listeptr yeni_liste(){
    Listeptr liste;
    liste = (Listeptr)malloc(sizeof(Liste));
    liste->bas=NULL;
    liste->son = NULL;
    return liste;
}

void liste_basina_ekle(Listeptr I, Elemanptr yeni){
    if(I->son == NULL) I->son = yeni;
    yeni->ileri = I->bas;
    I->bas = yeni;
}

void liste_sonuna_ekle(Listeptr I, Elemanptr yeni){
    if(I->bas==NULL) I->bas = yeni;
    else I->son->ileri=yeni;
    I->son = yeni;
}

void liste_yaz(Listeptr I){
    
    Elemanptr ptr;
    if(I==NULL) return;
    ptr=I->bas;
    while(ptr!=NULL) {
        printf("%5d ",ptr->icerik);
        ptr=ptr->ileri;
    }
    printf("\n");
}

void liste_sirali_ekle(Listeptr I, Elemanptr yeni){
    Elemanptr onceki,simdiki;
    onceki=NULL;
    simdiki=I->bas;
    while(simdiki!=NULL && simdiki->icerik < yeni->icerik){
        onceki=simdiki;
        simdiki=simdiki->ileri;
    }
    if(I->bas==NULL) {
        I->bas=I->son=yeni;
    }
    else if(simdiki==I->bas) {
       yeni->ileri=I->bas;
       I->bas=yeni;
    }
    else {
        onceki->ileri=yeni;
        yeni->ileri=simdiki;
    }
    
}

void liste_sirala(Listeptr I){
    Elemanptr simdiki,sonraki;
    if(I->bas == I->son) return;
    simdiki=I->bas->ileri;
    I->bas->ileri=NULL;
    I->son=I->bas;
    while(simdiki!=NULL){
        sonraki=simdiki->ileri;
        simdiki->ileri=NULL;
        liste_sirali_ekle(I,simdiki);
        simdiki=sonraki;
    }
}

void liste_eleman_sil(Listeptr I, int silinen){
    Elemanptr simdiki,onceki;
    simdiki=I->bas;
    while(simdiki!=NULL && simdiki->icerik!=silinen) {
        onceki=simdiki;
        simdiki=simdiki->ileri;
    }
    
    if(simdiki==NULL) return;
    else if(simdiki==I->bas) {
        I->bas=I->bas->ileri;
        if(simdiki==I->son) I->son = I->bas;
    }
    else{
        onceki->ileri=simdiki->ileri;
        if(simdiki==I->son) I->son = onceki;
    }  
}

void liste_yaz_tersten(Elemanptr liste_basi){
    //if(liste_basi!=NULL){
    if(liste_basi){
        liste_yaz_tersten(liste_basi->ileri);
        printf("%5d ",liste_basi->icerik);
    }
    
}

void liste_sil(Listeptr *I){
    Elemanptr simdiki,sonraki;
    simdiki=(*I)->bas;
    while(simdiki!=NULL){
        sonraki=simdiki->ileri;
        free(simdiki);
        simdiki=sonraki;
    }
    free(*I);
    *I=NULL;
}

struct eleman **ters(struct eleman **liste_basi){
    struct eleman *gecici;
    if(*liste_basi==NULL) return liste_basi;
    else if((*liste_basi)->ileri==NULL) return &((*liste_basi)->ileri);
    else {
        gecici=*liste_basi;
        *liste_basi=(*liste_basi)->ileri;
        *ters(liste_basi)=gecici;
         gecici->ileri=NULL;
        return &(gecici->ileri);
       
    }
}

int main(int argc, char** argv) {
    Listeptr liste1;
    Listeptr sirali;
    
    liste1=yeni_liste();
    liste_basina_ekle(liste1,yeni_eleman(20));
    liste_basina_ekle(liste1,yeni_eleman(80));
    liste_sonuna_ekle(liste1,yeni_eleman(-50));
    liste_sonuna_ekle(liste1,yeni_eleman(-30));
    liste_sonuna_ekle(liste1,yeni_eleman(-100));
    liste_sonuna_ekle(liste1,yeni_eleman(300));
    liste_sonuna_ekle(liste1,yeni_eleman(76));
    liste_sonuna_ekle(liste1,yeni_eleman(67));
    
    liste_yaz(liste1);
    printf("\n");
    
    ters(&(liste1->bas));
    liste_yaz(liste1);
    printf("\n");
    
    
    
    return (EXIT_SUCCESS);
}
