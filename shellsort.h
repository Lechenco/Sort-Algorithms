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

    int *A = NULL;
    int comp = 0, swap = 0;
private:
    int n;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

};

#endif // SHELLSORT_H
