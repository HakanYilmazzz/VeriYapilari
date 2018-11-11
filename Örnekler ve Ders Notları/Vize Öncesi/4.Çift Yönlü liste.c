#include <stdio.h>
#include <stdlib.h>

struct ciftYonluEleman {
        int icerik;
        struct ciftYonluEleman *ileri;
        struct ciftYonluEleman *geri;
};

struct ciftYonluListe {
        struct ciftYonluEleman *bas;
        struct ciftYonluEleman *son;
};

struct ciftYonluEleman *elemanOlustur(int icerik){
        struct ciftYonluEleman *yeni;

        yeni=(struct ciftYonluEleman*)malloc(sizeof(struct ciftYonluEleman));
        if(yeni==NULL) {
                printf("Hata, yer ayrilamadi. Sonlaniyor...");
                exit(1);
        }
        yeni->icerik =icerik;
        yeni->geri=yeni->ileri = NULL;
        return yeni;
}

void ciftYonluListeBaslat(struct ciftYonluListe **liste){
        *liste=(struct ciftYonluListe*)malloc(sizeof(struct ciftYonluListe));
        if(*liste==NULL) {
                printf("Hata, yer ayrilamadi. Sonlaniyor...");
                exit(1);
        }
        (*liste)->bas=(*liste)->son=NULL;
}

void liste_basina_ekle(int icerik,struct ciftYonluListe *liste){
        struct ciftYonluEleman *yeni;
        yeni=elemanOlustur(icerik);
        if(liste->son==NULL) liste->son=yeni;
        else{
                liste->bas->geri=yeni;
                yeni->ileri=liste->bas;
        }
        liste->bas=yeni;
}

void liste_sonuna_ekle(int icerik,struct ciftYonluListe *liste){
        struct ciftYonluEleman *yeni;
        yeni=elemanOlustur(icerik);
        if(liste->bas==NULL) liste->bas=yeni;
        else {
                liste->son->ileri=yeni;
                yeni->geri=liste->son;
        }
        liste->son=yeni;
}

void liste_yazdir(struct ciftYonluListe *liste){
        struct ciftYonluEleman *bas=liste->bas;
        while(bas!=NULL) {
                printf("%4d ",bas->icerik);
                bas=bas->ileri;
        }
        printf("\n");
}

void liste_yazdir_yanlis(struct ciftYonluListe *liste){
        //struct ciftYonluEleman *bas=liste->bas;
        while(liste->bas!=NULL) {
                printf("%4d ",liste->bas->icerik);
                liste->bas=liste->bas->ileri;
        }
        printf("\n");
}



void liste_yazdir_sondan(struct ciftYonluListe *liste){
        struct ciftYonluEleman *son=liste->son;
        while(son!=NULL) {
                printf("%4d ",son->icerik);
                son=son->geri;
        }
        printf("\n");

}



int main(int argc, char** argv) {

        struct ciftYonluListe *liste;
        ciftYonluListeBaslat(&liste);

        liste_basina_ekle(40,liste);
        liste_sonuna_ekle(60,liste);
        liste_basina_ekle(90,liste);
        liste_sonuna_ekle(5,liste);
        liste_yazdir_yanlis(liste);
        liste_yazdir_yanlis(liste);

        //  liste_yazdir_sondan(liste);


        return 0;
}
