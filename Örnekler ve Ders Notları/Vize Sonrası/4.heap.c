#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct dugum{
    int key;
    char *ad;
};

struct heap{
    struct dugum *dizi;
    int kapasite; // dizinin toplam tutabilecegi dugum sayisi
    int eleman_sayisi; // aktif dugum sayisi
};

//---------------------------------------------------------------------------------------------//

struct heap *heap_olustur(int kapasite){
    struct heap *gecici;
    gecici=(struct heap*)malloc(sizeof(struct heap));

    if(gecici==NULL){
        printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }

    gecici->dizi=(struct dugum*)malloc(kapasite*sizeof(struct dugum));

    if(gecici->dizi==NULL){
            printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }

    gecici->kapasite=kapasite;
    gecici->eleman_sayisi=0;
    return gecici;
}

//---------------------------------------------------------------------------------------------//

void print_heap(struct heap *heap){
    int i;
    for(i=0; i<heap->eleman_sayisi; i++) printf("%3d",heap->dizi[i].key);
    	printf("\n");
}

//---------------------------------------------------------------------------------------------//

void initialize_heap(struct heap *heap, int eleman_sayisi, int aralik){
    int i,j;
    int yeni,cik;
    srand(time(NULL));
    
    heap->dizi[0].key=rand()%aralik;

    for(i=1; i<eleman_sayisi; i++){//for

        while(1){/////
            cik=1;
            yeni=rand()%aralik;

            for(j=0; j<i; j++){//

                if(yeni==heap->dizi[j].key){
                    cik=0; break;
                }

            }//

            if(cik==0) continue;
            	heap->dizi[i].key=yeni;
            break;
        }/////

    }//for

    heap->eleman_sayisi=eleman_sayisi;
}  

//---------------------------------------------------------------------------------------------//

void buble_down(struct heap *heap, int index){
    int sol,sag;
    sol=2*index+1;
    sag=2*index+2;
    int temp_key;
    
    while((sol<heap->eleman_sayisi && 
            heap->dizi[index].key <heap->dizi[sol].key) ||
           (sag<heap->eleman_sayisi && 
            heap->dizi[index].key <heap->dizi[sag].key)){
        if(sag>=heap->eleman_sayisi ||
                heap->dizi[sol].key >heap->dizi[sag].key){
            temp_key = heap->dizi[sol].key;
            heap->dizi[sol].key = heap->dizi[index].key;
            heap->dizi[index].key=temp_key;
            index=2*index+1;
        }
        else {
            temp_key = heap->dizi[sag].key;
            heap->dizi[sag].key = heap->dizi[index].key;
            heap->dizi[index].key=temp_key;
            index=2*index+2;
        }
        sol=2*index+1;
        sag=2*index+2;
    } 
    
}

//---------------------------------------------------------------------------------------------//

void heapify(struct heap *heap){
    int i;
    for(i=heap->eleman_sayisi/2 -1; i>=0; i--) buble_down(heap,i);
}

//---------------------------------------------------------------------------------------------//

void buble_up(struct heap *heap,int index){
    int parent, temp_key;
    
    parent= (index-1)/2;
    while(index>=0 && heap->dizi[parent].key <heap->dizi[index].key){
  //  while( heap->dizi[parent].key <heap->dizi[index].key && parent>=0){  
        temp_key = heap->dizi[parent].key;
        heap->dizi[parent].key = heap->dizi[index].key;
        heap->dizi[index].key = temp_key;
        index = parent;
        parent =(index-1)/2;
    }
}

//---------------------------------------------------------------------------------------------//

void heap_insert(struct heap *heap, int key){
    if(heap->eleman_sayisi<heap->kapasite){
        heap->eleman_sayisi++;
        heap->dizi[heap->eleman_sayisi-1].key=key;
        buble_up(heap,heap->eleman_sayisi-1);
    }
}

//---------------------------------------------------------------------------------------------//

void delete_max(struct heap *heap){
    int temp_key;
    if(heap->eleman_sayisi>1){
        temp_key=heap->dizi[0].key;
        heap->dizi[0].key=heap->dizi[heap->eleman_sayisi-1].key;
        heap->dizi[heap->eleman_sayisi-1].key=temp_key;
        heap->eleman_sayisi--;
        buble_down(heap,0);
    }
}

//---------------------------------------------------------------------------------------------//

void heap_sort(struct heap *heap){
    int i;
    int temp=heap->eleman_sayisi;
    
    for(i=1;i<temp; i++){
        delete_max(heap);
    }
    heap->eleman_sayisi=temp;
    
}

//---------------------------------------------------------------------------------------------//
//--------------------------------------------main---------------------------------------------//
//---------------------------------------------------------------------------------------------//

int main(int argc, char** argv) {

    struct heap *heap;
    heap=heap_olustur(90);
    initialize_heap(heap,90,90);
    print_heap(heap);
    heapify(heap);
    print_heap(heap);
    
   
    
 
    
 //    delete_max(heap);
 //    print_heap(heap);
    
  //  delete_max(heap);
  //  print_heap(heap);
    
      heap_sort(heap);
      printf("Siralanmis dizi...\n");
      print_heap(heap);
    
  //  print_heap(heap);
    
    
  //  dizi_sirala(heap);
  //  printf("Siralanmis dizi...\n");
  //  print_heap(heap);        
    
    return (EXIT_SUCCESS);
}
