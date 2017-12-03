#include <stdio.h>
#include <stdlib.h>

void imprimir(int A[], int *n){

    int i;

    for(i=0; i<n; i++){
        printf(" %d", A[i]);
    }
}

void selection_sort(int A[], int n){

    int i, j, menor, aux;

    imprimir(A, n);

    for(i = 0; i < n-1; i++){

        menor = i;

        for(j = i+1; j < n; j++){

            if(A[j] < A[menor])
                menor = j;
        }

        aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
    }

    printf("\n");

    imprimir(A, n);
}

void insertion_sort(int A[], int n){

    int i, j, chave;

    imprimir(A, n);

    for(j=1; j<n; j++){

       chave = A[j];
       i = j-1;

        while(i>=0 && A[i]>chave){
            A[i+1] = A[i];
            i = i-1;
        }

         A[i+1] = chave;
    }

    printf("\n");

    imprimir(A, n);
}

void bubble_sort(int A[], int n){

    int i, j, aux;

    imprimir(A, n);

    for(i=1; i<n; i++){

        for(j=0; j<n-1; j++){

            if(A[j]>A[j+1]){
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
            }
        }
    }

    printf("\n");

    imprimir(A, n);

}

int partition(int A[], int p, int r){

    int q, i, aux=0;

    q = p;

    for(i=p; i<r; i++){

        if(A[i]<=A[r]){
            aux = A[q];
            A[q] = A[i];
            A[i] = aux;
            q++;
        }
    }

    aux = A[q];
    A[q] = A[r];
    A[r] = aux;

    return q;
}

int quicksort(int A[], int p, int r){

    int q, i;

    if(p>=r)
        return 0;

    else{
        q = partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

int main(){

    int vet[] = {3,4,9,2,5,1,8,6,3};

    //selection_sort(vet, 9);

    //insertion_sort(vet, 9);

    //bubble_sort(vet, 9);

    /*
    imprimir(vet, 9);
    quicksort(vet, 0, 9);
    printf("\n");
    imprimir(vet, 9);
    */

    return 0;
}
