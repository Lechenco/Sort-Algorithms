#include "selectionsort.h"
#include <QTime>
#include <cstdlib>

SelectionSort::SelectionSort(QObject *parent) : QObject(parent)
{

}

void SelectionSort::selectionSort(int n){

    int i, j, menor, aux;

    for(i = 0; i < n-1; i++){

        menor = i;

        for(j = i+1; j < n; j++){

            if(++comp && A[j] < A[menor])
                menor = j;
            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 400){

            }

            emit resultReady();
        }

        aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
        ++swap;
    }

}

void SelectionSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}

void SelectionSort::doWork(){
    comp = 0; swap = 0;
    this->selectionSort(n);
}
