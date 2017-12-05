#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <QObject>

class RadixSort : public QObject
{
    Q_OBJECT
public:
    explicit RadixSort(QObject *parent = nullptr);
    void radixSort(int size);
    int findLargestNum(int size);
    void setN(int n);

    int *A = NULL;
    int comp = 0, swap = 0;

signals:
    void resultReady();

public slots:
    void doWork();

private:
    int n;
};

#endif // RADIXSORT_H
