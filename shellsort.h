#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <QObject>
#include <QtCharts>

class ShellSort : public QObject
{
    Q_OBJECT
public:
    explicit ShellSort(QObject *parent = nullptr);
    void setSet(QBarSet *s);
    void shellsort();

    int comp = 0, swap = 0;
private:
    QBarSet * s;

signals:
    void resultReady();
    void greenPeace(int x);

public slots:
    void doWork();

};

#endif // SHELLSORT_H
