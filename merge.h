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

    //Achar outra forma de passar vetores entre classes <vector>
    int A[30];

signals:
    void resultReady();

public slots:
    void doWork();
};

#endif // MERGE_H
