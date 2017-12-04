#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void bubble_sort(int n);
    void setN(int n);

    int A[30];
signals:
    void resultReady();

public slots:
    void doWork();

private:
    int n;
};

#endif // BUBBLESORT_H
