#include "quicksort.h"
#include <QTime>

QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}
int QuickSort::partition(int p, int r){

    int q, i, aux=0;

    q = p;

    for(i=p; i<r; i++){

        if(A[i]<=A[r]){
            aux = A[q];
            A[q] = A[i];
            A[i] = aux;
            q++;
        }
        QTime *tmp = new QTime();
        tmp->start();
        while(tmp->elapsed() < 100){

        }

        emit resultReady();
    }

    aux = A[q];
    A[q] = A[r];
    A[r] = aux;

    return q;
}

void QuickSort::quicksort(int p, int r){

    int q;

    if(p>=r)
        return;

    else{
        q = partition(p,r);
        quicksort(p,q-1);
        quicksort(q+1,r);
    }
}

void QuickSort::setN(int n){
    this->n = n;
}

void QuickSort::doWork(){
    this->quicksort(0, n);

}
