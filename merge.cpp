#include "merge.h"
#include <cstdio>
#include <cstdlib>
#include <QTime>

Merge::Merge(QObject *parent) : QObject(parent)
{

}

void Merge::setSet(QBarSet *s){
    this->s = s;
}

void Merge::merge(int p, int q, int r){
        int i, j, k;
        int n1 = q - p +1;
        int n2 = r - q;

        int *L = (int*) malloc(sizeof(int) * (n1 + 1));
        int *R = (int*) malloc(sizeof(int) * (n2 + 1));


        for(i = 0; i < n1; i++){
                L[i] = s->at(p + i);
        }

        for(j = 0; j < n2; j++, i++){
                R[j] = s->at(p + i);
        }

        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        i = 0;
        j = 0;

        for(k = p; k <= r; k++){
                if(L[i] < R[j]){
                        s->replace(k, L[i]);
                        i++;

                }else{
                        s->replace(k, R[j]);
                        j++;

                }
                comp++;
                ++swap;

                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 200){

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
    this->mergeSort(0, s->count());
    emit greenPeace(1);
}
