#include "bubblesort.h"
#include <QTime>
#include <cstdlib>

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::bubble_sort(){

    int i, j, aux;

    for(i=1; i<n; i++){

        for(j=0; j<n-i; j++){

            if(++comp && A[j]>A[j+1]){
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
                ++swap;
            }

            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() <200){

            }

            emit resultReady();
        }
    }
}

void BubbleSort::doWork(){
    comp = 0; swap = 0;
    this->bubble_sort();
    emit greenPeace(2);
}

void BubbleSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);

}
