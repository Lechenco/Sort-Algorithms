#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <QObject>

class ShellSort : public QObject
{
    Q_OBJECT
public:
    explicit ShellSort(QObject *parent = nullptr);

     void shellsort(int *vet, int n);
signals:
      void update();

public slots:

};

#endif // SHELLSORT_H
