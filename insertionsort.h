#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <QObject>

class InsertionSort : public QObject
{
    Q_OBJECT
public:
    explicit InsertionSort(QObject *parent = nullptr);
    void insertion_sort(int n);
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

#endif // INSERTIONSORT_H
