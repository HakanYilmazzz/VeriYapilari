/*
 * File:   main.c
 * Author: BMB
 *
 * Created on 22 Ekim 2013 Salı, 12:53
 */

#include <stdio.h>
#include <stdlib.h>

/*
 *
 */

struct ciftYonluEleman{
    int icerik;
    struct ciftYonluEleman *ileri;
    struct ciftYonluEleman *geri;
};

struct ciftYonluListe{
    struct ciftYonluEleman *bas;
    struct ciftYonluEleman *son;
};

struct ciftYonluEleman* elemanOlustur(int icerik){
   struct ciftYonluEleman *elemanPtr;
   elemanPtr=(struct ciftYonluEleman*)malloc(sizeof(struct ciftYonluEleman));
   elemanPtr->icerik=icerik;
   elemanPtr->geri=elemanPtr->ileri=NULL;
   return elemanPtr;
}

struct ciftYonluListe* ciftYonluListeOlustur(){
    struct ciftYonluListe *liste;
    liste=(struct ciftYonluListe*)malloc(sizeof(struct ciftYonluListe));
    liste->bas=liste->son=NULL;
    //(*liste).bas=(*liste).son=NULL;
    return liste;
}

void liste_basina_ekle(struct ciftYonluEleman *eleman,struct ciftYonluListe* liste){
    if(liste->son==NULL) liste->son=eleman;
    else {
        liste->bas->geri=eleman;
        eleman->ileri=liste->bas;
    }
    liste->bas=eleman;
}

void liste_sonuna_ekle(struct ciftYonluEleman *eleman,struct ciftYonluListe* liste){
    if(liste->bas==NULL) liste->bas=eleman;
    else {
        liste->son->ileri=eleman;
        eleman->geri=liste->son;
    }
    liste->son=eleman;
}

void liste_yazdir(struct ciftYonluListe* liste){
  struct ciftYonluEleman* elemanPtr;
  elemanPtr=liste->bas;
  while(elemanPtr!=NULL){
      printf("%4d ",elemanPtr->icerik);
      elemanPtr=elemanPtr->ileri;
  }
}

void liste_yazdir_sondan(struct ciftYonluListe* liste){
  struct ciftYonluEleman* elemanPtr;
  elemanPtr=liste->son;
  while(elemanPtr!=NULL){
      printf("%4d ",elemanPtr->icerik);
      elemanPtr=elemanPtr->geri;
  }
}

int eleman_sayisi(struct ciftYonluEleman *elemanPtr){
     if(elemanPtr==NULL) return 0;
     return 1+eleman_sayisi(elemanPtr->ileri);
}




int main(int argc, char** argv) {
    struct ciftYonluListe *liste;
    liste=ciftYonluListeOlustur();
    liste_basina_ekle(elemanOlustur(100),liste);
    liste_basina_ekle(elemanOlustur(500),liste);
    liste_sonuna_ekle(elemanOlustur(700),liste);
    liste_sonuna_ekle(elemanOlustur(900),liste);
    liste_yazdir(liste);
    printf("\n");
    liste_yazdir_sondan(liste);
    printf("\n");
    printf("Eleman sayisi: %4d\n",eleman_sayisi(liste->bas));
    return (EXIT_SUCCESS);
}
