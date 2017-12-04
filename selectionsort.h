#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <QObject>

class SelectionSort : public QObject
{
    Q_OBJECT
public:
    explicit SelectionSort(QObject *parent = nullptr);
    void selectionSort(int n);
    void setN(int n);

    int A[30];
    int comp = 0, swap = 0;

signals:
    void resultReady();

public slots:
    void doWork();

private:
    int n;

};

#endif // SELECTIONSORT_H
