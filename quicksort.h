#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <QObject>

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void quicksort(int p, int r);
    int partition(int p, int r);
    void setN(int n);

    int A[30];

signals:
    void resultReady();

public slots:
    void doWork();

private:
    int n;
};

#endif // QUICKSORT_H
