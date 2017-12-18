#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <QObject>
#include <QtCharts>

class InsertionSort : public QObject
{
    Q_OBJECT
public:
    explicit InsertionSort(QObject *parent = nullptr);
    void insertion_sort(int n);
    void setSet(QBarSet * s);

    int comp = 0, swap = 0;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

private:
    QBarSet * s;
};

#endif // INSERTIONSORT_H
