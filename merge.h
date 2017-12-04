#ifndef MERGE_H
#define MERGE_H

#include <QObject>


class Merge : public QObject
{
    Q_OBJECT
public:
    explicit Merge(QObject *parent = nullptr);
    void merge(int p, int q, int r);
    void mergeSort(int p, int r);
    void setN(int n);

    //Achar outra forma de passar vetores entre classes <vector>
    int A[30];
    int comp = 0, swap = 0;

signals:
    void resultReady();

public slots:
    void doWork();

private:
    int n;
};

#endif // MERGE_H
