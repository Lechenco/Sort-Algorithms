#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <QObject>
#include <QtCharts>

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void quicksort(int left, int right);
    int partition(int p, int r);
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

#endif // QUICKSORT_H
