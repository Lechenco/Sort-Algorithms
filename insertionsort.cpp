#include "insertionsort.h"
#include <QTime>
#include <cstdlib>

InsertionSort::InsertionSort(QObject *parent) : QObject(parent)
{

}

void InsertionSort::setSet(QBarSet *s){
    this->s = s;
}

void InsertionSort::insertion_sort(int n){

    int i, j, chave;

    for(j=1; j<n; j++){

       chave = s->at(j);
       i = j-1;

        while(++comp && i>=0 && s->at(i) > chave){
            s->replace(i+1, s->at(i));
            i = i-1;
            ++swap;

            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 200){

            }

            emit resultReady();
        }

         s->replace(i+1, chave);
    }
}

void InsertionSort::doWork(){
    comp = 0; swap = 0;
    this->insertion_sort(s->count());
    emit greenPeace(4);

}
