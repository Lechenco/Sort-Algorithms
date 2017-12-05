#include "insertionsort.h"
#include <QTime>
#include <cstdlib>

InsertionSort::InsertionSort(QObject *parent) : QObject(parent)
{

}

void InsertionSort::insertion_sort(int n){

    int i, j, chave;

    for(j=1; j<n; j++){

       chave = A[j];
       i = j-1;

        while(++comp && i>=0 && A[i]>chave){
            A[i+1] = A[i];
            i = i-1;
            ++swap;

            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 400){

            }

            emit resultReady();
        }

         A[i+1] = chave;
    }
}

void InsertionSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}

void InsertionSort::doWork(){
    comp = 0; swap = 0;
    this->insertion_sort(n);

}
