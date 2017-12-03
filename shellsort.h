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
private:
    int n;

signals:
    void resultReady();

public slots:
    void doWork();

};

#endif // SHELLSORT_H
