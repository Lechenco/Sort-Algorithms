#include "quicksort.h"
#include <QTime>
#include <cstdlib>

QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}

void QuickSort::quicksort(int left, int right){

    int i = left, j = right;
          int tmp;
          int pivot = A[(left + right) / 2];

          /* partition */
          while (i <= j) {
                while (++comp && A[i] < pivot)
                      i++;
                while (++comp && A[j] > pivot)
                      j--;
                if (i <= j) {
                      tmp = A[i];
                      A[i] = A[j];
                      A[j] = tmp;
                      i++;
                      j--;
                      ++swap;
                }
                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 1000){

                }

                emit resultReady();
          };

          /* recursion */
          if (left < j)
                quicksort(left, j);
          if (i < right)
                quicksort(i, right);
}

void QuickSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}

void QuickSort::doWork(){
    comp = 0; swap = 0;
    this->quicksort(0, n);
   // partition(0, n);
}
