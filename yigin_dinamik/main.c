/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 04 Kasım 2013 Pazartesi, 03:16
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#define SENTINAL -1000000;

struct eleman{
    int icerik;
    struct eleman *link;
};


struct eleman* eleman_olustur(int icerik){
    struct eleman *e;
    e=(struct eleman*)malloc(sizeof(struct eleman));
    e->icerik=icerik;
    e->link = NULL;
    return e;
}

void yigina_eleman_ekle(struct eleman **yigin_isaretcisi,
        int icerik){
    struct eleman *e=eleman_olustur(icerik);
    e->link=*yigin_isaretcisi;
    *yigin_isaretcisi=e;
}

int yigin_bosmu(struct eleman *yigin_isaretcisi){
    if(yigin_isaretcisi==NULL) return 1;
    return 0;           
}

struct eleman* yigindan_eleman_cikar(struct eleman **yigin_isaretcisi){
    struct eleman *cikarilan=*yigin_isaretcisi;
    *yigin_isaretcisi=(*yigin_isaretcisi)->link;
    return cikarilan;
}

int yigindan_eleman_cikar1(struct eleman **yigin_isaretcisi){
    struct eleman *cikarilan;
    int dondurulen;
    
    if(yigin_bosmu(*yigin_isaretcisi)){
       return SENTINAL; 
    }
    cikarilan=*yigin_isaretcisi;
    dondurulen=cikarilan->icerik;
    *yigin_isaretcisi=(*yigin_isaretcisi)->link;
    free(cikarilan);
    return dondurulen;
}
void yigin_yaz(struct eleman *yigin_isaretcisi){
    printf("Yigini Yaziyorum...\n");
    while(yigin_isaretcisi!=NULL){
        printf("%4d ",yigin_isaretcisi->icerik);
        yigin_isaretcisi=yigin_isaretcisi->link;
    }
    printf("\n");
}

void yigin_yaz_recursive(struct eleman *yigin_isaretcisi){
    if(yigin_isaretcisi==NULL) {
        printf("\n");
        return;
    }
    printf("%4d ",yigin_isaretcisi->icerik);
    yigin_yaz_recursive(yigin_isaretcisi->link);
    
            
}
int main(int argc, char** argv) {
    struct eleman *yigin_isaretcisi;
    int cikarilan;
    yigin_isaretcisi=NULL;
    yigina_eleman_ekle(&yigin_isaretcisi,5);
    
    yigina_eleman_ekle(&yigin_isaretcisi,15);
    yigina_eleman_ekle(&yigin_isaretcisi,2);
    yigin_yaz_recursive(yigin_isaretcisi);
    cikarilan=yigindan_eleman_cikar1(&yigin_isaretcisi);
    cikarilan=yigindan_eleman_cikar1(&yigin_isaretcisi);
    cikarilan=yigindan_eleman_cikar1(&yigin_isaretcisi);
    cikarilan=yigindan_eleman_cikar1(&yigin_isaretcisi);
    yigin_yaz(yigin_isaretcisi);
    
    return (EXIT_SUCCESS);
}

