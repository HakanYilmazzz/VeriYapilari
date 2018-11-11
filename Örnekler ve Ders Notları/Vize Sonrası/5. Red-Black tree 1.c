#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct red_black_node{
    char colour;
    int key;
    struct red_black_node *left,*right,*parent;
};

struct red_black_tree{
    struct red_black_node *root;
};
///---------------------------------------------------------------------------------------------------///
void red_black_tree_olustur(struct red_black_tree **agac){
    *agac=(struct red_black_tree*)malloc(sizeof(struct red_black_tree));
    if(*agac==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->root=NULL;  
}
///---------------------------------------------------------------------------------------------------///
struct red_black_node* red_black_dugum_olustur(){
    struct red_black_node *d = (struct red_black_node*)malloc(sizeof(struct red_black_node));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
 //   d->key = key; //
    d->left=d->right=NULL;
 //   d->colour=BLACK;
    return d;
}
///---------------------------------------------------------------------------------------------------///
void red_black_tree_preorder_yardimci(struct red_black_node *root){
    
    if(root==NULL) return;
    if(root->left!=NULL && root->right!=NULL) printf("%4d",root->key);
    else printf("  ex"); 
    if(root->colour==RED) printf("(R)");
    else printf("(B)");
    red_black_tree_preorder_yardimci(root->left);
    red_black_tree_preorder_yardimci(root->right);
    
}
///---------------------------------------------------------------------------------------------------///
void red_black_tree_preorder(struct red_black_tree *T){
    if(T==NULL) return;
    red_black_tree_preorder_yardimci(T->root);
    printf("\n");
}
///---------------------------------------------------------------------------------------------------///
void left_rotate(struct red_black_tree *T, struct red_black_node *x){
    struct red_black_node *y;
    y = x->right;
    x->right = y->left;
    if(y->left!=NULL) y->left->parent = x;
    y->parent=x->parent;
    if(x->parent==NULL) T->root=y;
    else {
        if(x==x->parent->left) x->parent->left=y;
        else x->parent->right = y;
    }
    y->left=x;
    x->parent=y;
}
///---------------------------------------------------------------------------------------------------///
void right_rotate(struct red_black_tree *T, struct red_black_node *x){
    struct red_black_node *y;
    y=x->left;
    x->left=y->right;
    if(y->right!=NULL) y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==NULL) T->root=y;
    else {
        if(x==x->parent->left) x->parent->left =y;
        else x->parent->right = y;
    }
    y->right= x;
    x->parent=y;
    
}
///---------------------------------------------------------------------------------------------------///
void red_black_tree_ekle(struct red_black_tree *T,int key){
    struct red_black_node *dugum;
    struct red_black_node *d,*d1;
    struct red_black_node *x,*y;
    
    x=red_black_dugum_olustur();
    x->key=key;
    x->colour=RED;
    
    if(T->root==NULL){
        x->parent=NULL;
        T->root = x;
        d=red_black_dugum_olustur(); //extternal node
        d->colour=BLACK;
        d->parent=x;
        x->left=d;
        
        d=red_black_dugum_olustur(); //external node
        d->colour=BLACK;
        d->parent=x;
        x->right=d;
   
      
        //return;  
      //  T->root->colour=black;
      //  return;        
    }   
    else{
         d=T->root;
        while(d->left!=NULL && d->right!=NULL){
            if(key < d->key) d=d->left;
            else if( key > d->key) d= d->right;
            else return;
        }  
  
        x->left=d;
        x->right=red_black_dugum_olustur(); //external dugum
        x->right->colour=BLACK;
        x->parent=d->parent;
    
        if(d==d->parent->left){
            d->parent->left=x;
        }
        else{
          d->parent->right=x;
        }   
        x->left->parent=x->right->parent=x;
        x->colour = RED;
    }
    
    while((x!=T->root) && (x->parent->colour == RED)){
        if(x->parent==x->parent->parent->left){
            y=x->parent->parent->right; // y is x's uncle
            if(y->colour==RED){
                // case 1 - change the colours
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x= x->parent->parent; // move up the tree
            }
            else {
                // y is a black node
                if(x==x->parent->right){
                    // case 2 - move x up and rotate
                    x=x->parent;
                    left_rotate(T,x);
                }
                // case 3 - x->parent->colour =black;
                x->parent->colour=BLACK;
                x->parent->parent->colour=RED;
                right_rotate(T,x->parent->parent);
            }
        }
        else {
            y=x->parent->parent->left; // y is x's uncle
            if(y->colour==RED){
                // case 1 - change the colours
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x= x->parent->parent; // move up the tree
            }
            else {
                // y is a black node
                if(x==x->parent->left){
                    // case 2 - move x up and rotate
                    x=x->parent;
                    right_rotate(T,x);
                }
                // case 3 - x->parent->colour =black;
                x->parent->colour=BLACK;
                x->parent->parent->colour=RED;
                left_rotate(T,x->parent->parent);
            }
        }
    }
    T->root->colour=BLACK;
    
}
///---------------------------------------------------------------------------------------------------///
///--------------------------------------------------main---------------------------------------------///
///---------------------------------------------------------------------------------------------------///
int main(int argc, char** argv) {
    struct red_black_tree *T=NULL;
    red_black_tree_olustur(&T);
    red_black_tree_preorder(T);
    
    red_black_tree_ekle(T,10);
    red_black_tree_ekle(T,80);
    red_black_tree_ekle(T,40);
    red_black_tree_ekle(T,4);
    red_black_tree_ekle(T,58);
    red_black_tree_ekle(T,68);
    red_black_tree_ekle(T,78);
    red_black_tree_ekle(T,16);
    red_black_tree_ekle(T,74);
    
    red_black_tree_ekle(T,178);
    red_black_tree_ekle(T,116);
    red_black_tree_ekle(T,743);
    
    red_black_tree_preorder(T);
   
  //  printf("Ic dugum sayisi: %4d\n",foo(agac->kok));
   
    return (EXIT_SUCCESS);
}
