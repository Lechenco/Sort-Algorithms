#include "bubblesort.h"
#include <QTime>

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::bubble_sort(int n){

    int i, j, aux;

    for(i=1; i<n; i++){

        for(j=0; j<n-i; j++){

            if(A[j]>A[j+1]){
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
            }

            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 200){

            }

            emit resultReady();
        }
    }
}

void BubbleSort::doWork(){
    this->bubble_sort(n);
}

void BubbleSort::setN(int n){
    this->n = n;

}
