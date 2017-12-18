#include "bubblesort.h"
#include <QTime>
#include <cstdlib>

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}

void BubbleSort::setSet(QBarSet *s){
    this->s = s;
}

void BubbleSort::bubble_sort(){

    int i, j, aux;

    for(i = 1; i < s->count(); i++){

        for(j = 0;  j< s->count() -i; j++){

            if(++comp && s->at(j) > s->at(j+1)){
                aux = s->at(j);
                s->replace(j, s->at(j+1));
                s->replace(j+1, aux);
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

