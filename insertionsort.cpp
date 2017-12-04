#include "insertionsort.h"
#include <QTime>

InsertionSort::InsertionSort(QObject *parent) : QObject(parent)
{

}

void InsertionSort::insertion_sort(int n){

    int i, j, chave;

    for(j=1; j<n; j++){

       chave = A[j];
       i = j-1;

        while(i>=0 && A[i]>chave){
            A[i+1] = A[i];
            i = i-1;

            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 200){

            }

            emit resultReady();
        }

         A[i+1] = chave;
    }
}

void InsertionSort::setN(int n){
    this->n = n;
}

void InsertionSort::doWork(){
    this->insertion_sort(n);
}
