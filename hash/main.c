/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 09 AralÄ±k 2013 Pazartesi, 01:02
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*
 * 
 */

struct CELL {
    char *soyad;
    struct CELL *next;
};

int lookup(char *soyad, struct CELL *l){
    if(l==NULL) return 0;
    else if(!strcmp(soyad,l->soyad)) return 1;
    else return lookup(soyad,l->next);
}

int insert(char *soyad, struct CELL **l){
    if(*l==NULL){
        *l=(struct CELL *)malloc(sizeof(struct CELL));
        (*l)->soyad = (char *)malloc((strlen(soyad)+1)*sizeof(char));
        strcpy((*l)->soyad,soyad);
        (*l)->next=NULL;
        return 1;
    }
    else if(strcmp(soyad,(*l)->soyad)) return insert(soyad,&((*l)->next));
    else return 0;
}

void print_list(struct CELL *l){
    if(l!=NULL){
        printf("%s ",l->soyad);
        print_list(l->next);
    }
}

struct table_node{
    int count;
    struct CELL *header;
};

struct hash_tablosu{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

#define TABLE_SIZE 11
#define MULTIPLIER 3
unsigned hash(char *s){
    int i=0;
    unsigned int value =0;
    while(s[i] != '\0'){
        value=(s[i]+MULTIPLIER*value) % TABLE_SIZE;
        i++;
    }
    return value;
}

unsigned hash1(char *s, int multiplier, int table_size){
    int i=0;
    unsigned int value =0;
    while(s[i] != '\0'){
        value=(s[i]+multiplier*value) % table_size;
        i++;
    }
    return value;
}


struct table_node* initialize_hash_table(){
    int i;
    struct table_node *hash_table;
    hash_table = (struct table_node*)malloc(TABLE_SIZE*sizeof(struct table_node));
    if(hash_table==NULL){
        printf("Hash hablosu icin gerekli yer ayrilamadi. Hata...");
        exit(1);
    }
    for(i=0; i<TABLE_SIZE; i++){
        (hash_table+i)->count=0;
        (hash_table+i)->header=NULL;
    }
    return hash_table;
}

void insert_hash_table(struct table_node *hash_table, char *soyad){
    insert(soyad,&(hash_table+hash(soyad))->header);
    hash_table[hash(soyad)].count++;
}

void hash_table_print(struct table_node *hash_table){
    if(hash_table!=NULL){
        int i;
        for(i=0; i<TABLE_SIZE; i++){
            printf("%5d : (%2d)",i,(hash_table+i)->count);
            print_list((hash_table+i)->header);
            printf("\n");
        }
    }
}

void initialize_hash_table1(struct hash_tablosu **hash_table,int multiplier,int tablo_uzunlugu){
    int i;
    
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   // *hash_table = (struct table_node*)malloc(TABLE_SIZE*sizeof(struct table_node));
    if(*hash_table==NULL){
        printf("Hash hablosu icin gerekli yer ayrilamadi. Hata...");
        exit(1);
    } 
    (*hash_table)->tablo_basi = (struct table_node*)malloc(tablo_uzunlugu*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL){
        printf("Hash hablosu icin gerekli yer ayrilamadi. Hata...");
        exit(1);
    }
    (*hash_table)->tablo_uzunlugu = tablo_uzunlugu;
    (*hash_table)->multiplier = multiplier;
    
    for(i=0; i<tablo_uzunlugu; i++){
        (((*hash_table)->tablo_basi)+i)->count=0;
       (((*hash_table)->tablo_basi)+i)->header=NULL;
    }
}

void insert_hash_table1(struct hash_tablosu *hash_table, char *soyad){
    int yerles;
    yerles=insert(soyad, &((hash_table->tablo_basi+hash1(soyad,hash_table->multiplier,hash_table->tablo_uzunlugu))->header));
     if(yerles) (hash_table->tablo_basi+
           hash1(soyad,hash_table->multiplier,hash_table->tablo_uzunlugu))->count++;
}

void hash_table_print1(struct hash_tablosu *hash_table){
    if(hash_table!=NULL){
        int i;
        printf("---- Hash Table icerigi----\n");
        for(i=0; i<hash_table->tablo_uzunlugu; i++){
            printf("%5d : (%2d) ",i,(hash_table->tablo_basi+i)->count);
            print_list((hash_table->tablo_basi+i)->header);
            printf("\n");
        }
    }
    else printf("\nHash table bos...\n");
}

void liste_yok_et(struct CELL **liste_basi){
    if(*liste_basi!=NULL) {
        struct CELL *gecici=*liste_basi;
        *liste_basi=(*liste_basi)->next;
        free(gecici->soyad);
        free(gecici);
    }
}

void liste_yok_et_recursive(struct CELL **liste_basi){
    if(*liste_basi!=NULL){
       liste_yok_et_recursive(&(*liste_basi)->next);
       free((*liste_basi)->soyad);
       free(*liste_basi);
    }
    *liste_basi=NULL;
}

void hash_table_yok_et(struct hash_tablosu **hash_table){
    int i;
    if(*hash_table!=NULL){
       for(i=0; i <(*hash_table)->tablo_uzunlugu; i++)
           liste_yok_et(&((*hash_table)->tablo_basi+i)->header);
    
       free((*hash_table)->tablo_basi);  
   }
   *hash_table=NULL; 
}    


 struct hash_tablosu* hash_tablosu_buyut(struct hash_tablosu **htable1,
         int multiplier,int tablo_uzunlugu){
     
     int i;
     struct CELL *liste_basi;
     struct hash_tablosu *htable2;
     if(*htable1==NULL) return NULL;
     initialize_hash_table1(&htable2,multiplier,tablo_uzunlugu);
     for(i=0; i<(*htable1)->tablo_uzunlugu; i++){
         liste_basi=((*htable1)->tablo_basi+i)->header;
         while(liste_basi!=NULL){
            insert_hash_table1(htable2, liste_basi->soyad);
            liste_basi=liste_basi->next;
         }
     }
     hash_table_yok_et(htable1);
     return htable2;
}
  
 /* void liste_eleman_sil(Listeptr I, int silinen){
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
 
 */
 
 
 void hash_table_delete(struct hash_tablosu *tablo, char *soyad){
 
     struct table_node *table_node;
     struct CELL *simdiki,*onceki;
     
     
     table_node=tablo->tablo_basi+hash1(soyad, tablo->multiplier,
          tablo->tablo_uzunlugu);
     
     simdiki=table_node->header;
     while(simdiki!=NULL && strcmp(simdiki->soyad,soyad)) {
        onceki=simdiki;
        simdiki=simdiki->next;
     }
     if(simdiki==NULL) return;
     if(simdiki==table_node->header) table_node->header=simdiki->next;
     else onceki->next=simdiki->next; 
     table_node->count--;
     
 }   
int main(int argc, char** argv) {
  /*  struct hash_tablosu htable;
    htable.tablo_basi=initialize_hash_table();
    htable.tablo_uzunlugu=TABLE_SIZE;
    
    insert_hash_table(htable.tablo_basi,"istanbul");
    insert_hash_table(htable.tablo_basi,"trabzon");
    insert_hash_table(htable.tablo_basi,"urfa");
    insert_hash_table(htable.tablo_basi,"kayseri");
    insert_hash_table(htable.tablo_basi,"bursa");
    insert_hash_table(htable.tablo_basi,"konya");
    insert_hash_table(htable.tablo_basi,"ordu");
    insert_hash_table(htable.tablo_basi,"rize");
    insert_hash_table(htable.tablo_basi,"zonguldak");
    insert_hash_table(htable.tablo_basi,"kocaeli");
    insert_hash_table(htable.tablo_basi,"canakkale");
    insert_hash_table(htable.tablo_basi,"nigde");
    insert_hash_table(htable.tablo_basi,"giresun");
    
    
    hash_table_print(htable.tablo_basi); */
    
    
    struct hash_tablosu *htable=NULL;
    
    initialize_hash_table1(&htable,3,11);
  
    
    insert_hash_table1(htable,"istanbul");
    insert_hash_table1(htable,"trabzon");
    insert_hash_table1(htable,"urfa");
    insert_hash_table1(htable,"kayseri");
    insert_hash_table1(htable,"bursa");
    insert_hash_table1(htable,"konya");
    insert_hash_table1(htable,"ordu");
    insert_hash_table1(htable,"rize");
    insert_hash_table1(htable,"zonguldak");
    insert_hash_table1(htable,"kocaeli");
    insert_hash_table1(htable,"canakkale");
    insert_hash_table1(htable,"nigde");
    insert_hash_table1(htable,"giresun");
    insert_hash_table1(htable,"adana");
    insert_hash_table1(htable,"mus");
    insert_hash_table1(htable,"kayseri");
    insert_hash_table1(htable,"balikesir");
    insert_hash_table1(htable,"gumushane");
    
    
    hash_table_print1(htable);
    
    htable=hash_tablosu_buyut(&htable,7,23);
    
    hash_table_print1(htable);
    
    htable=hash_tablosu_buyut(&htable,89,101);
    hash_table_print1(htable);
    
    hash_table_delete(htable, "bursa");
    hash_table_print1(htable);
    
    return (EXIT_SUCCESS);
}
