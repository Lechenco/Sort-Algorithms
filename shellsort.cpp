#include "shellsort.h"
#include <QTime>
#include <cstdlib>

ShellSort::ShellSort(QObject *parent) : QObject(parent)
{

}

void ShellSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}

void ShellSort::shellsort(int *vet){
    int h = 1;
    int i, j, chave;

    do{
        h = 3*h + 1;
    }while(h < n);

    do{
        h /= 3;
        for(i = h; i < n; i++){
            chave = vet[i];
            j = i;
            while(++comp && j >= h && vet[j - h] > chave){
                vet[j] = vet[j - h];
                j -= h;
                ++swap;

                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 1000){

                }

                emit resultReady();
            }
            vet[j] = chave;
            ++swap;
        }

    }while(h != 1);
    emit finish();
}

void ShellSort::doWork(){
    comp = 0; swap = 0;
    this->shellsort(A);

}

