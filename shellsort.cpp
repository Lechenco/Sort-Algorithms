#include "shellsort.h"
#include <QTime>

ShellSort::ShellSort(QObject *parent) : QObject(parent)
{

}

void ShellSort::setN(int n){
    this->n = n;

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
            while(j >= h && vet[j - h] > chave){
                vet[j] = vet[j - h];
                j -= h;

                 QTime *tmp = new QTime();
                 tmp->start();
                 while(tmp->elapsed() < 200){

                 }

                 emit resultReady();
            }
            vet[j] = chave;
        }

    }while(h != 1);
}

void ShellSort::doWork(){

    this->shellsort(A);

}

