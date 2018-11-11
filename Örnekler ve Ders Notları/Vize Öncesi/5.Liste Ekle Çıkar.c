#include <stdio.h>
#include <stdlib.h>

struct eleman {
        int tip;
        int islenen;
        int oncelik;
        char islem;
        struct eleman *ileri;
};


struct eleman* yeni_islenen(int islenen){
        struct eleman *e;
        e=(struct eleman*)malloc(sizeof(struct eleman));
        e->tip=0; // islenen
        e->islenen = islenen;
        e->ileri=NULL;
        return e;
}

struct eleman* yeni_islem(char islem){
        struct eleman *e;
        e =(struct eleman*)malloc(sizeof(struct eleman));
        e->tip = 1;
        e->islem = islem;
        switch(islem) {
        case '(': e->oncelik=0;
                break;
        case '+':
        case '-': e->oncelik=1;
                break;
        case '*':
        case '/': e->oncelik=2;
                break;
        case ')': e->oncelik=3;
                break;
        }
        e->ileri=NULL;
        return e;
}

struct liste {
        struct eleman *bas;
        struct eleman *son;
};

struct liste* yeni_liste(){
        struct liste *l;
        l = (struct liste*)malloc(sizeof(struct liste));
        l->bas=NULL;
        l->son = NULL;
        return l;
}

void liste_sonuna_ekle(struct liste* l, struct eleman* yeni){
        if(l->bas==NULL) l->bas = yeni;
        else l->son->ileri=yeni;
        l->son = yeni;
}

void liste_yaz(struct liste* l){
        struct eleman *e;
        if(l==NULL) return;
        e=l->bas;
        while(e!=NULL) {
                if(e->tip==0) printf("%d ",e->islenen);
                else printf("%c ",e->islem);
                e=e->ileri;
        }
        printf("\n");
}

void yigina_eleman_ekle(struct eleman **yigin_isaretcisi,struct eleman *e){

        e->ileri=*yigin_isaretcisi;

        *yigin_isaretcisi=e;
}

int yigin_bosmu(struct eleman *yigin_isaretcisi){
        if(yigin_isaretcisi==NULL) return 1;
        return 0;
}

struct eleman* yigindan_eleman_cikar(struct eleman **yigin_isaretcisi){
        struct eleman *cikarilan=*yigin_isaretcisi;
        *yigin_isaretcisi=(*yigin_isaretcisi)->ileri;

        return cikarilan;
}

struct eleman* yigin_ust(struct eleman *yigin_isaretcisi){
        return yigin_isaretcisi;
}

void infix_olustur(struct liste **l){
        *l=yeni_liste();
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islenen(1));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(17));
        liste_sonuna_ekle(*l,yeni_islem(')'));
        liste_sonuna_ekle(*l,yeni_islem('*'));

        liste_sonuna_ekle(*l,yeni_islenen(4));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(5));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islenen(3));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(1));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islenen(6));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(3));
        liste_sonuna_ekle(*l,yeni_islem(')'));
        liste_sonuna_ekle(*l,yeni_islem(')'));
        liste_sonuna_ekle(*l,yeni_islem('/'));
        liste_sonuna_ekle(*l,yeni_islenen(4));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(4));

        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(1));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(17));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islenen(2));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(6));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islenen(2));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islenen(3));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(4));
        liste_sonuna_ekle(*l,yeni_islem('/'));
        liste_sonuna_ekle(*l,yeni_islenen(3));

        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islenen(2));
        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islenen(7));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(5));
        liste_sonuna_ekle(*l,yeni_islem(')'));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(4));
        liste_sonuna_ekle(*l,yeni_islem('+'));
        liste_sonuna_ekle(*l,yeni_islenen(2));

        liste_sonuna_ekle(*l,yeni_islem('*'));
        liste_sonuna_ekle(*l,yeni_islem('('));
        liste_sonuna_ekle(*l,yeni_islenen(4));
        liste_sonuna_ekle(*l,yeni_islem('-'));
        liste_sonuna_ekle(*l,yeni_islenen(5));
        liste_sonuna_ekle(*l,yeni_islem(')'));
        liste_sonuna_ekle(*l,yeni_islem(')'));



}

void postfix_olustur(struct liste *in, struct liste **out){
        struct eleman *yigin = NULL;
        struct eleman *bas=in->bas;
        struct eleman *e,*e1;
        struct eleman *ust;
        *out=yeni_liste();

        while(bas!=NULL) {
                if(bas->tip==0) liste_sonuna_ekle(*out,yeni_islenen(bas->islenen));
                else {
                        if(bas->islem == '(') yigina_eleman_ekle(&yigin,yeni_islem('('));
                        else if (bas->islem == ')') {
                                e=yigindan_eleman_cikar(&yigin);
                                while(e->islem!='(') {
                                        liste_sonuna_ekle(*out,yeni_islem(e->islem));
                                        e=yigindan_eleman_cikar(&yigin);
                                }
                        }
                        else {

                                ust=yigin_ust(yigin);

                                while(ust!=NULL && bas->oncelik <=ust->oncelik) {

                                        e1 = yigindan_eleman_cikar(&yigin);
                                        //     printf("Bburasi: %c\n",e1->islem);
                                        liste_sonuna_ekle(*out,yeni_islem(e1->islem));
                                        ust=yigin_ust(yigin);
                                }

                                yigina_eleman_ekle(&yigin,yeni_islem(bas->islem));
                                //printf("Burasi: %c\n",bas->islem);
                        }
                }

                bas=bas->ileri;
        }
        while(yigin_bosmu(yigin)==0) {

                e1=yigindan_eleman_cikar(&yigin);

                liste_sonuna_ekle(*out,yeni_islem(e1->islem));
        }

}

int postfix_hesapla(struct liste *in){
        struct eleman *yigin = NULL;
        struct eleman *bas=in->bas;
        struct eleman *e1,*e2;
        int sonuc;
        while(bas!=NULL) {
                if(bas->tip==0) {
                        yigina_eleman_ekle(&yigin,yeni_islenen(bas->islenen));

                }
                else {

                        e1=yigindan_eleman_cikar(&yigin);
                        e2=yigindan_eleman_cikar(&yigin);

                        if(bas->islem=='+') sonuc = e2->islenen + e1->islenen;
                        else if(bas->islem=='-') sonuc = e2->islenen - e1->islenen;
                        else if(bas->islem=='*') sonuc = e2->islenen * e1->islenen;
                        else sonuc = e2->islenen / e1->islenen;
                        yigina_eleman_ekle(&yigin,yeni_islenen(sonuc));
                }
                bas=bas->ileri;
        }
        e1=yigindan_eleman_cikar(&yigin);



        return e1->islenen;
}

int main(int argc, char** argv) {

        struct liste* l1;
        struct liste* l2;
        int sonuc;
        infix_olustur(&l1);
        liste_yaz(l1);
        postfix_olustur(l1, &l2);
        liste_yaz(l2);
        sonuc=postfix_hesapla(l2);
        printf("Sonuc: %d\n",sonuc);



        return (EXIT_SUCCESS);
}
