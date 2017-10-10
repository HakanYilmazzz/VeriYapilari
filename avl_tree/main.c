/* 
 * File:   main.c
 * Author: BMB
 *
 * Created on 30 Kasım 2013 Cumartesi, 21:14
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

// AVL agac dugumu

 struct node{
    int key;
    
    struct node *left;
    struct node *right;
    int height;
};

struct node *newNode(int key){
    struct node *node=(struct node*)malloc(sizeof(struct node));
    node->key=key;
    node->left=node->right=NULL;
    node->height=1;
    return node;
}

int max(int a, int b){
    return a>b ? a: b;
}

int height(struct node *N){
    if(N==NULL) return 0;
    return N->height;
}
struct node *rightRotate(struct node *y){
    struct node *x=y->left;
    struct node *T= x->right;
    
    x->right = y;
    y->left = T;
    
    // Yukseklikleri guncelle
    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;
    
    
    return x; 
}

struct node *leftRotate(struct node *x){
    struct node *y=x->right;
    struct node *T=y->left;
    
    y->left=x;
    x->right=T;
    
    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
    
    return y;
}

int getBalance(struct node *n){
    if(n==NULL) return 0;
    return height(n->left) - height(n->right);
}

struct node* insert(struct node* node, int key){
    int balance;
    if(node == NULL) return newNode(key);
    
    if(key < node->key) node->left = insert(node->left,key);
    else node->right = insert(node->right,key);
    
    // agacın yuksekligini guncelle
    
    node->height=max(height(node->left),height(node->right))+1;
    
    balance=getBalance(node);
    
    // sol sol durumu
    if(balance>1 && key < node->left->key) 
        return rightRotate(node);
    // sag sag durumu
    if(balance<-1 && key > node->right->key)
        return leftRotate(node);
    // sol sag
    if(balance>1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
    }
    // sag sol 
    if(balance <-1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    } 
    
    return node;
} 
        
void preOrder(struct node *root){
    if(root!=NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

struct node *minValueNode(struct node* node){
    struct node * current = node;
    if(current==NULL) return NULL;
    while(current->left) current=current->left;
    return current;
}

struct node *deleteNode(struct node* root, int key){
    if(root==NULL) return root;
    
    if(key < root->key) root->left = deleteNode(root->left,key);
    else if(key > root->key)  root->right = deleteNode(root->right,key);
    else {
        if(root->left == NULL || root->right==NULL) {
            struct node *temp= root->left ? root->left : root->right;
            
           // child yok (silinecek dugum yaprak)
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else {
                  //*root=*temp;
                   root->height=temp->height;
                   root->key=temp->key;
                   root->left=temp->left;
                   root->right=temp->right;
            }
            free(temp);
       }
        else {
            // iki child var
            struct node *temp= minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        } 
        
}
    if(root==NULL) return root;
    
    root->height=max(height(root->left),height(root->right)) +1;
    int balance=getBalance(root);
    
    // sol sol durumu
    if(balance >1 && getBalance(root->left) >=0)
        return rightRotate(root);
    
    // sol sag durumu
    if(balance >1 && getBalance(root->left) <0){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    
    // sag sag
    if(balance <-1 && getBalance(root->right) <=0)
        return leftRotate(root);
    
    // sag sol
    if(balance < -1 && getBalance(root->right) >0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
   
int yaprak_sayisi(struct node *root){
    if(root==NULL) return 0;
    if(root->left==NULL && root->right==NULL) return 1;
    return yaprak_sayisi(root->left)+yaprak_sayisi(root->right);
}



int main(){
     struct node *root=NULL;
    
     root=insert(root,100);
     root=insert(root,50);
     root=insert(root,200);
     root=insert(root,25);
     root=insert(root,80);
     root=insert(root,70);
     root=insert(root,75);
     root=deleteNode(root,80);
     root=deleteNode(root,70);
     root=deleteNode(root,100);
     root=deleteNode(root,200);
     preOrder(root);
   //  printf("\n");
   //  root=deleteNode(root,80);
  //   preOrder(root);
     
     
     
     
  //   printf("\n");
    
  //   printf("Yaprak Sayisi: %d\n",yaprak_sayisi(root));
     return (EXIT_SUCCESS);
        
   
    
    
    
}
