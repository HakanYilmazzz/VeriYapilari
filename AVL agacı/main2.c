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
int binary_search_tree_mi(struct red_black_node *node, struct red_black_tree *T){
    struct red_black_node *a;
    if(node==NULL) return 1;
    else if(node->left==NULL) return 1;
    else if(node->left->left!=NULL && node->key<node->left->key) return 0;
    else if (node->right->right!=NULL && node->key > node->right->key) return 0;
    else {
        a=T->root;
        while (a->left!=NULL &&a!=node){
            if(node->key < a->key ) a=a->left;
            else if (node->key>a->key) a=a->right;
            else break;
        }
        if(a!=node) return 0;
        if(binary_search_tree_mi(node->left,T)) return binary_search_tree_mi(node->right,T);
        else return 0;
    }
}
///---------------------------------------------------------------------------------------------------///
int renk_kontrolu(struct red_black_node *root){
    int static i=0;
    if(i==0) {
        if(root->colour==RED) return 0;
        i=1;
    }
    if(root->left==NULL && root->colour==RED) return 0;
    else if(root->left==NULL && root->colour == BLACK) return 1;
    else if(root->colour==RED && (root->left->colour == RED || root->right->colour==RED))
        return 0;
    else if(renk_kontrolu(root->left)) return renk_kontrolu(root->right);
    else return 0;
}
///---------------------------------------------------------------------------------------------------///
int yapraktan_koke_kadar_siyah_dugum_say(struct red_black_node *node){

    int i=0;
    while(node!=NULL){
        if(node->colour==BLACK) i++;
            node = node->parent;
    }
    return i;
}
///---------------------------------------------------------------------------------------------------///
int siyah_dugum_sayilari_kontrolu(struct red_black_node *root) {
    static int i=0;
    static int siyah_dugum_sayisi=0;
    struct red_black_node *a;
    struct red_black_node *a1=root;
    int x;

    if(i==0){
        a= root;
        while(a->left!=NULL) a=a->left;
        siyah_dugum_sayisi=yapraktan_koke_kadar_siyah_dugum_say(a);
        i=1;
    }
    if(root==NULL) return 1;
    else if(root->left==NULL) {
        if(yapraktan_koke_kadar_siyah_dugum_say(root) != siyah_dugum_sayisi) return 0;
        return 1;
    }
    else {
        x=siyah_dugum_sayilari_kontrolu(root->left);
        if(x)
            return siyah_dugum_sayilari_kontrolu(root->right) return 1;  //hatalı
        else return 0;
    }
}
///---------------------------------------------------------------------------------------------------///
int red_black_tree_mi(struct red_black_tree *T){

    if(binary_search_tree_mi(T->root,T) && renk_kontrolu(T->root) && siyah_dugum_sayilari_kontrolu (T->root))
        return 1;
    else return 0;
}



int main(int argc, char** argv) {
    struct red_black_tree *T=NULL;
    
    red_black_tree_olustur(&T);
    // red_black_tree_preorder(T);

    red_black_tree_ekle(T,91);
    red_black_tree_ekle(T,20);
    red_black_tree_ekle(T,400);
    red_black_tree_ekle(T,40);
    
    printf("%d", red_black_tree_mi(T));
}
