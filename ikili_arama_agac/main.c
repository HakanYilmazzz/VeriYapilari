/* 
 * File:   main.c
 * Author: kadayif
 *
 * Created on 11 Kasım 2013 Pazartesi, 10:57
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


struct dugum {
    int eleman;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_agac{
    struct dugum *kok;
};

struct dugum* dugum_olustur(int eleman){
    struct dugum *d;
    d=(struct dugum*)malloc(sizeof(struct dugum));
    d->eleman=eleman;
    d->sol=d->sag=NULL;
    return d;
}

void ikili_agac_olustur(struct ikili_agac **agac){
    *agac=(struct ikili_agac*)malloc(sizeof(struct ikili_agac));
    (*agac)->kok=NULL;
}

void ikili_agac_eleman_ekle(struct ikili_agac *agac, int eleman){
    struct dugum *dugum;
    struct dugum *d;
    struct dugum *geri;
    
    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(eleman < d->eleman) d=d->sol;
        else if(eleman > d->eleman) d=d->sag;
        else return; // eleaman tekrari yok
    }
    
    dugum=dugum_olustur(eleman);
    if(agac->kok==NULL){
        agac->kok=dugum;
        return;
    }
    if(eleman<geri->eleman) geri->sol=dugum;
    else geri->sag=dugum;    
}

void ikili_agac_eleman_sil(struct ikili_agac *agac, int silinen){
    struct dugum *d=agac->kok;
    struct dugum *parent=NULL;
    struct dugum *d1,*d2;;
    int sol_sag;  // 0 sol, 1 sag
    while(d!=NULL){     
        if(silinen < d->eleman)   { parent=d; d=d->sol; sol_sag=0;}
        else if(silinen > d->eleman) { parent=d; d=d->sag; sol_sag=1;}
        else break;
    }
    if(d==NULL) return; //eleman agacta yok!
    
    if(d->sol==NULL){ // silinen dugumun solu bos
        if(d==agac->kok) agac->kok=d->sag;
        else {
            if(sol_sag==0) parent->sol=d->sag;
            else parent->sag =d->sag;
        }   
    }
    else if(d->sag==NULL){ // silinen dugumun sagi bos
        if(d==agac->kok)agac->kok=d->sol;
        else {
            if(sol_sag==0) parent->sol=d->sol;
            else parent->sag=d->sol;
        }       
    }
    else { // silinen dugumun hem sagi hem de solu dolu
        d1=d->sol;
        while(d1->sag!=NULL) d1=d1->sag;
        if(d1!=d->sol){
            d2=d->sol;
            while(d2->sag!=d1) d2=d2->sag;
            d2->sag=d1->sol;
            d1->sol=d->sol;
            
        }
        d1->sag=d->sag;
        if(parent!=NULL){
              if(sol_sag==0) parent->sol=d1;
              else parent->sag=d1; 
        } 
        else { // kok degisti
              if(d1==d->sol) agac->kok=d->sol;
              else agac->kok=d1; 
        }          
    } 
    free(d);
}


struct dugum* minValueNode(struct dugum *node){
    struct dugum *current = node;
    if(node==NULL) return node;
    while(current->sol!=NULL) current=current->sol;
    return current;
}

struct dugum *deleteDugum(struct dugum *root, int key){
    if(root==NULL) return root;
    if(key < root->eleman) root->sol=deleteDugum(root->sol,key);  
    else if(key > root->eleman) root->sag=deleteDugum(root->sag,key);
    else {
        // note with only one child or no child 
        if(root->sol == NULL || root->sag == NULL) {
            struct dugum *temp= root->sol ? root->sol : root->sag;
            
         //   if(root->sol!=NULL) temp=root->sol;
         //   else temp=root->sag;
            
            if(temp== NULL ){ // no child
                temp = root;
                root = NULL;
                
            }
            else { // single child
                root->eleman = temp->eleman;
                root->sol = temp->sol;
                root->sag = temp->sag;
            }
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct dugum *temp= minValueNode(root->sag);
            // copy the inorder succeror's data to this node
            
            
            root->eleman = temp->eleman;
            root->sag= deleteDugum(root->sag, temp->eleman);   
        }    
    }
    return root;
}




void inorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    inorder_yaz(kok->sol);
    printf("%3d ",kok->eleman);
    inorder_yaz(kok->sag);
    
}

void preorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    printf("%3d ",kok->eleman);
    preorder_yaz(kok->sol);
    preorder_yaz(kok->sag);
    
}

void postorder_yaz(struct dugum* kok){
    if(kok==NULL) return;
    
    postorder_yaz(kok->sol);
    postorder_yaz(kok->sag);
    printf("%3d ",kok->eleman);
    
}


int dugum_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    return 1+dugum_sayisi(kok->sol)+dugum_sayisi(kok->sag);
    
}




int main(int argc, char** argv) {
    struct ikili_agac *agac;
    //struct ikili_agac *agac1=ikili_agac_olustur1();
    ikili_agac_olustur(&agac);   
    ikili_agac_eleman_ekle(agac, 100);  
    ikili_agac_eleman_ekle(agac, 50);
    ikili_agac_eleman_ekle(agac, 200);
    ikili_agac_eleman_ekle(agac, 25);
    ikili_agac_eleman_ekle(agac, 75);
    ikili_agac_eleman_ekle(agac, 125);
    ikili_agac_eleman_ekle(agac, 300);
    ikili_agac_eleman_ekle(agac, 175);
    ikili_agac_eleman_ekle(agac, 350);
    ikili_agac_eleman_ekle(agac, 150);
    ikili_agac_eleman_ekle(agac, 325);
    ikili_agac_eleman_ekle(agac, 135);
    ikili_agac_eleman_ekle(agac, 165);
    ikili_agac_eleman_ekle(agac, 290);
   // ikili_agac_eleman_ekle(agac, 200);
    
    inorder_yaz(agac->kok);
    printf("\n");
    
    agac->kok=deleteDugum(agac->kok,300);
    //agac->kok=deleteDugum(agac->kok,300);
    // agac->kok=deleteDugum(agac->kok,200);
    //agac->kok=deleteDugum(agac->kok,100);
    
    
  //    ikili_agac_eleman_sil(agac,300);
 //   ikili_agac_eleman_sil(agac,200);
 //   ikili_agac_eleman_sil(agac,100);
    
    inorder_yaz(agac->kok);
    printf("\n");
    
    
   
    
    //  ikili_agac_eleman_sil(agac, 100);
  //    inorder_yaz(agac->kok);
  //    printf("\n");
    
    printf("Dugum Sayisi: %d\n",dugum_sayisi(agac->kok));
    
    
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}


