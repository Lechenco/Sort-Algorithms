#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>
#include <QtCharts>

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void bubble_sort();
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

#endif // BUBBLESORT_H
