#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <QObject>
#include <QtCharts>

class SelectionSort : public QObject
{
    Q_OBJECT
public:
    explicit SelectionSort(QObject *parent = nullptr);
    void selectionSort(int n);
    void setSet(QBarSet * s);

    int comp = 0, swap = 0;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

private:
    QBarSet *s;

};

#endif // SELECTIONSORT_H
