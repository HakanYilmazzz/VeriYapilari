#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -10000000

struct yigin {
        int *dizi;
        int ust;
        int kapasite;
};

struct yigin* yigin_olustur(int kapasite){
        if(kapasite<=0) {
                printf("Kapasite pozitif bir tam sayi olmali... ");
                exit(1);
        }
        struct yigin *ptr=(struct yigin*)malloc(sizeof(struct yigin));
        ptr->dizi=(int *)malloc(kapasite*sizeof(int));
        ptr->ust=-1;
        ptr->kapasite= kapasite;
        return ptr;
}

void yigin_olustur_parametre_ile(int kapasite, struct yigin **y){
        if(kapasite<=0) {
                printf("Kapasite pozitif bir tam sayi olmali... ");
                exit(1);
        }
        *y=(struct yigin*)malloc(sizeof(struct yigin));
        (*y)->dizi=(int *)malloc(kapasite*sizeof(int));
        (*y)->ust=-1;
        (*y)->kapasite=kapasite;
}

int yigin_bosmu(struct yigin *y){
        if(y->ust==-1) return 1;
        else return 0;
}
int yigin_dolumu(struct yigin *y){
        if(y->ust==y->kapasite-1) return 1;
        else return 0;
}

void yigin_ekle(int eleman, struct yigin *y){
        if(yigin_dolumu(y)) {
                printf("Yigin dolu, ekleme yapilamiyor...");
                return;
        }
        y->dizi[++y->ust]=eleman;

}

void yigin_yaz(struct yigin *y){
        int i;
        printf("Yigin Kapasitesi       :%4d\n",y->kapasite);
        printf("Yigindaki Eleman Sayisi:%4d\n",y->ust+1);
        for(i=y->ust; i>=0; i--) {
                printf("%4d ",y->dizi[i]);
        }
        printf("\n");
}

int yigin_eleman_sil(struct yigin *y){
        if(yigin_bosmu(y)) return SENTINEL;
        return y->dizi[y->ust--];


}

void yigin_yok_et(struct yigin **y){
        free((*y)->dizi);
        free(*y);
        *y=NULL;
}

struct yigin *kapasiteyi_artir(struct yigin **ptr, int kackat){
        struct yigin *yeni;
        int i;
        yeni=yigin_olustur(kackat*((*ptr)->kapasite));
        for(i=0; i<=(*ptr)->ust; i++) yeni->dizi[i]=(*ptr)->dizi[i];
        yeni->ust=(*ptr)->ust;
        yigin_yok_et(&(*ptr)); // yigin_yok_et(ptr);
        return yeni;
}

void kapasiteyi_artir_yeni(struct yigin **ptr, int kackat){
        struct yigin *yeni;
        int i;
        yeni=yigin_olustur(kackat*((*ptr)->kapasite));
        for(i=0; i<=(*ptr)->ust; i++) yeni->dizi[i]=(*ptr)->dizi[i];
        yeni->ust=(*ptr)->ust;
        yigin_yok_et(&(*ptr)); // yigin_yok_et(ptr);
        *ptr=yeni;
}


int main(int argc, char** argv) {
        struct yigin *A=NULL;
        struct yigin *B=NULL;
        int silinen;
        A=yigin_olustur(10);
        // yigin_olustur_parametre_ile(10,&A);
        yigin_ekle(12,A);
        yigin_ekle(56,A);
        yigin_ekle(-20,A);
        yigin_yaz(A);

        silinen=yigin_eleman_sil(A);
        printf("Silinen: %4d\n",silinen);
        yigin_yaz(A);

        yigin_ekle(100,A);
        yigin_yaz(A);

        kapasiteyi_artir_yeni(&A,3);
        yigin_yaz(A);

        return (EXIT_SUCCESS);
}
