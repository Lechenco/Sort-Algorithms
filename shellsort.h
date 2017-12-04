#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <QObject>

class ShellSort : public QObject
{
    Q_OBJECT
public:
    explicit ShellSort(QObject *parent = nullptr);
    void setN(int n);
    void shellsort(int *vet);

    int A[30];
    int comp = 0, swap = 0;
private:
    int n;

signals:
    void resultReady();
    void finish();

public slots:
    void doWork();

};

#endif // SHELLSORT_H
