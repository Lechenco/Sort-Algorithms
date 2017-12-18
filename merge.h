#ifndef MERGE_H
#define MERGE_H

#include <QObject>
#include <QtCharts>


class Merge : public QObject
{
    Q_OBJECT
public:
    explicit Merge(QObject *parent = nullptr);
    void merge(int p, int q, int r);
    void mergeSort(int p, int r);
    void setSet(QBarSet *s);

    int comp = 0, swap = 0;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

private:
    QBarSet * s;
};

#endif // MERGE_H
