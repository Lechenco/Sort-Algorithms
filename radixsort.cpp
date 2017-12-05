#include "radixsort.h"
#include <QTime>
#include <cstdlib>

RadixSort::RadixSort(QObject *parent) : QObject(parent)
{

}

int RadixSort::findLargestNum(int size){

  int i;
  int largestNum = -1;

  for(i = 0; i < size; i++){
    if(A[i] > largestNum)
      largestNum = A[i];
  }

  return largestNum;
}

void RadixSort::radixSort(int size){

  // Base 10 is used
  int i;
  int semiSorted[size];
  int significantDigit = 1;
  int largestNum = findLargestNum(size);

  // Loop until we reach the largest significant digit
  while (largestNum / significantDigit > 0){

    int bucket[10] = { 0 };

    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < size; i++)
      bucket[(A[i] / significantDigit) % 10]++;

    /**
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the array
         * Works similar to the count sort algorithm
     **/
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];

    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(A[i] / significantDigit) % 10]] = A[i];


    for (i = 0; i < size; i++){
      A[i] = semiSorted[i];
      swap++;

      QTime *tmp = new QTime();
      tmp->start();
      while(tmp->elapsed() < 400){

      }

      emit resultReady();

    }

    // Move to next significant digit
    significantDigit *= 10;

  }
}

void RadixSort::doWork(){
    comp = 0; swap = 0;
    this->radixSort(n);

}
void RadixSort::setN(int n){
    this->n = n;
    free(A);
    A = (int*) malloc(sizeof(int) * n);
}
