#include "quicksort.h"
#include <QTime>
#include <cstdlib>

QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}

void QuickSort::setSet(QBarSet *s){
    this->s = s;
}

void QuickSort::quicksort(int left, int right){

    int i = left, j = right;
          int tmp;
          int pivot = s->at((left + right) / 2);

          /* partition */
          while (i <= j) {
                while (++comp && s->at(i) < pivot)
                      i++;
                while (++comp && s->at(j) > pivot)
                      j--;
                if (i <= j) {
                      tmp = s->at(i);
                      s->replace(i, s->at(j));
                      s->replace(j, tmp);
                      i++;
                      j--;
                      ++swap;
                }
                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 200){

                }

                emit resultReady();
          };

          /* recursion */
          if (left < j)
                quicksort(left, j);
          if (i < right)
                quicksort(i, right);
}

void QuickSort::doWork(){
    comp = 0; swap = 0;
    this->quicksort(0, s->count());
    emit greenPeace(3);
}
