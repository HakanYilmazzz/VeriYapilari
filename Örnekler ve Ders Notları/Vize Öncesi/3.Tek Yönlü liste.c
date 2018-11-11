#include <stdio.h>
#include <stdlib.h>
/*-------------------------------------------------------------*/
struct hucre {
        int icerik;
        struct hucre *sonraki;
};
/*-------------------------------------------------------------*/
struct hucre* hucre_olustur(int icerik) {
        struct hucre *a;
        a = (struct hucre*)malloc(sizeof(struct hucre));
        if (a==NULL) {
                printf("Heap alaninda yer ayrilamadi.\n");
                exit(1);
        }
        a->icerik = icerik;
        a->sonraki = NULL;
        return a;
}
/*-------------------------------------------------------------*/
void liste_basina_ekle(int icerik, struct hucre **liste_basi) {
        struct hucre* a = hucre_olustur(icerik);
        a->sonraki = *liste_basi;
        *liste_basi = a;
}
/*-------------------------------------------------------------*/
void liste_sonuna_ekle(int icerik, struct hucre **liste_basi) {
        struct hucre* a = hucre_olustur(icerik);
        if(*liste_basi == NULL) {
                a->sonraki = *liste_basi;
                *liste_basi = a;
        }
        else {
                struct hucre* x = *liste_basi;
                while(x->sonraki != NULL) {
                        x = x->sonraki;
                }
                x->sonraki = a;
        }
}
/*-------------------------------------------------------------*/
void liste_yaz(struct hucre *liste_basi) {
        while(liste_basi != NULL) {
                printf("%d  ", liste_basi->icerik);
                liste_basi = liste_basi->sonraki;
        }
        printf("\n");
}
/*-------------------------------------------------------------*/
void liste_yaz_recursive(struct hucre *liste_basi) {
        if(liste_basi != NULL) {
                printf("%d  ", liste_basi->icerik);
                liste_yaz_recursive(liste_basi->sonraki);
        }
        else {
                printf("\n");
        }
}
/*-------------------------------------------------------------*/
void tersten_listeyaz_recursive(struct hucre *liste_basi) {
        if(liste_basi != NULL) {
                tersten_listeyaz_recursive(liste_basi->sonraki);
                printf("%d ", liste_basi->icerik);
        }
}
/*-------------------------------------------------------------*/
void liste_yok_et(struct hucre **liste_basi) {
        struct hucre *simdiki;
        while(*liste_basi != NULL) {
                // printf("%d elemani yok edildi.\n", (*liste_basi)->icerik);
                simdiki = *liste_basi;
                *liste_basi = (*liste_basi)->sonraki; //(->)ok, (*)yıldızdan daha öncelikli. Paranteze dikkat.
                free(simdiki);
        }
        printf("Liste yok edildi, adresler temizlendi.\n");
}
/*-------------------------------------------------------------*/
void liste_sirali_ekle(int icerik, struct hucre **liste_basi) {
        struct hucre *a, *b, *eklenen;
        b = *liste_basi;
        while(b != NULL && b->icerik <= icerik) {
                // if(b->icerik == icerik) {
                //         return;
                // } /*Aynı elemanı eklemeyi engeller.*/
                a = b;
                b = b->sonraki;
        }
        eklenen = hucre_olustur(icerik);
        if (b == *liste_basi) {
                eklenen->sonraki = *liste_basi;
                *liste_basi = eklenen;
        }
        else {
                a->sonraki = eklenen;
                eklenen->sonraki = b;
        }
} //Sınav sorusu olabilir.
/*-------------------------------------------------------------*/
void liste_eleman_sil(int silinen, struct hucre **liste_basi) {
        //değişiklik olasılığı olduğundan liste başının adresi gönderilir.**
        struct hucre *temp = *liste_basi;
        struct hucre *once;
        while((temp != NULL) && (temp->icerik != silinen)) {
                once = temp;
                temp = temp->sonraki;
        }
        if (temp == NULL) {
                return;
        }
        else if (temp == *liste_basi) {
                *liste_basi =(*liste_basi)->sonraki;
        }
        else {
                once->sonraki = temp->sonraki;
        }
        free(temp);
}
/*-------------------------------------------------------------*/
void liste_sirala(struct hucre **liste_basi) {
        struct hucre *a, *b, *c, *d;
        if (*liste_basi == NULL || (*liste_basi)->sonraki == NULL) {
                return;
        } //Listede bir elemandan fazla olmalı.
        d=(*liste_basi)->sonraki;
        (*liste_basi)->sonraki = NULL;
        while(d != NULL) {
                c = d;
                d = d->sonraki;
                b = *liste_basi;
                while(b != NULL && b->icerik < c->icerik) {
                        a = b;
                        b = b->sonraki;
                }
                if(b == *liste_basi) {
                        c->sonraki = *liste_basi;
                        *liste_basi = c;
                }
                else {
                        a->sonraki = c;
                        c->sonraki = b;
                }
        }
}
/*-------------------------------------------------------------*/
void liste_ters_cevir(struct hucre **liste_basi) {
        struct hucre *a, *b;
        a = NULL;
        while(*liste_basi != NULL) {
                b = *liste_basi;
                *liste_basi = (*liste_basi)->sonraki;
                b->sonraki = a;
                a = b;
        }
        *liste_basi = a;
}
/*-------------------------------------------------------------*/
struct hucre **liste_ters_cevir_recursive(struct hucre **liste_basi) {
        struct hucre *gecici;
        if (*liste_basi == NULL) {
                return liste_basi;
        }
        else if ((*liste_basi)->sonraki == NULL) {
                return &((*liste_basi)->sonraki);
        }
        else {
                gecici = *liste_basi;
                *liste_basi = (*liste_basi)->sonraki;
                *liste_ters_cevir_recursive(liste_basi) = gecici;
                gecici->sonraki = NULL;
                return &(gecici->sonraki);
        }
}
/*-------------------------------------------------------------*/
int main(int argc, char const *argv[]) {
        struct hucre *liste1 = NULL;

        /*Eleman Ekleme*/
        liste_basina_ekle(30, &liste1);
        liste_basina_ekle(40, &liste1);
        liste_basina_ekle(50, &liste1);
        liste_basina_ekle(60, &liste1);
        liste_basina_ekle(70, &liste1);
        liste_sonuna_ekle(10, &liste1);
        liste_sonuna_ekle( 0, &liste1);

        /*Liste Yazdırma*/
        liste_yaz(liste1);
        //liste_yaz_recursive(liste1);
        //tersten_listeyaz_recursive(liste1);

        /*Liste Yok Et*/
        liste_yok_et(&liste1);

        /*Sıralı eleman ekleme*/
        liste_sirali_ekle(16, &liste1);
        liste_sirali_ekle(13, &liste1);
        liste_sirali_ekle(45, &liste1);
        liste_sirali_ekle(73, &liste1);
        liste_sirali_ekle(99, &liste1);
        liste_sirali_ekle(57, &liste1);
        liste_sirali_ekle(39, &liste1);
        liste_yaz(liste1);

        /*Eleman Silme*/
        liste_eleman_sil(13, &liste1);
        liste_eleman_sil(57, &liste1);
        liste_yaz(liste1);

        /*Liste Yok Et*/
        liste_yok_et(&liste1);

        /*Eleman ekleme: başına, sonuna ve sıralı*/
        liste_sonuna_ekle(10, &liste1);
        liste_basina_ekle(10, &liste1);
        liste_sonuna_ekle(20, &liste1);
        liste_basina_ekle(40, &liste1);
        liste_basina_ekle(50, &liste1);
        liste_basina_ekle(60, &liste1);
        liste_basina_ekle(70, &liste1);
        liste_sirali_ekle(43, &liste1);
        liste_sirali_ekle(53, &liste1);
        liste_sirali_ekle(53, &liste1);
        liste_yaz(liste1);

        /*Listeyi Sırala*/
        liste_sirala(&liste1);
        liste_yaz(liste1);

        /*Listeyi Ters Çevir*/
        liste_ters_cevir(&liste1);
        liste_yaz(liste1);

        /*Listeyi Ters Çevir Recursive*/
        liste_ters_cevir_recursive(&liste1);
        liste_yaz(liste1);

        return 0;
}
