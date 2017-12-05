#include "merge.h"
#include <cstdio>
#include <cstdlib>
#include <QTime>

Merge::Merge(QObject *parent) : QObject(parent)
{

}

void Merge::merge(int p, int q, int r){
        int i, j, k;
        int n1 = q - p +1;
        int n2 = r - q;

        int *L = (int*) malloc(sizeof(int) * (n1 + 1));
        int *R = (int*) malloc(sizeof(int) * (n2 + 1));


        for(i = 0; i < n1; i++){
                L[i] = A[p + i];
        }

        for(j = 0; j < n2; j++, i++){
                R[j] = A[p + i];
        }

        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        i = 0;
        j = 0;

        for(k = p; k <= r; k++){
                if(L[i] < R[j]){
                        A[k] = L[i];
                        i++;

                }else{
                        A[k] = R[j];
                        j++;

                }
                comp++;
                ++swap;

                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 1000){

                }

                emit resultReady();

        }

}

void Merge::mergeSort(int p, int r){
        int q;
       // Merge *aux = new Merge();

        if(p < r){
                q = (p + r)/2;
                this->mergeSort( p, q);
                this->mergeSort(q+1, r);
                this->merge(p, q, r);

        }

}

void Merge::doWork(){
    comp = 0; swap = 0;
    this->mergeSort(0, n);

}

void Merge::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}
