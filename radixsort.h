#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <QObject>
#include <QtCharts>

class RadixSort : public QObject
{
    Q_OBJECT
public:
    explicit RadixSort(QObject *parent = nullptr);
    void radixSort(int size);
    int findLargestNum(int size);
    void setSet(QBarSet * s);
    void setN(int n);

    int *A = NULL;
    int comp = 0, swap = 0;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

private:
    int n;
    QBarSet * s;
};

#endif // RADIXSORT_H
