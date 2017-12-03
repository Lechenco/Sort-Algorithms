#ifndef PLOTHISTO_H
#define PLOTHISTO_H
#define TAM 30

#include <QWidget>
#include <QtCharts>
#include <QThread>

class QPushButton;
class QLabel;
class Merge;
class ShellSort;
class PlotHisto : public QWidget
{
    Q_OBJECT
    QThread workerthread;
public:
    explicit PlotHisto(QWidget *parent = nullptr);
    void mergeSort(int p, int r);
    void merge(int p, int q, int r);
    void updateArrays();

public slots:
    //void handleResults();
    void randomArray();
    void invertArray();
    void updateChart();

signals:
    void operate();

private:
     Merge *m;
     ShellSort *s;


    int n = TAM, count = 0;

    QBarSet *set0;
    QList<QChartView *> m_chartView;
    QPushButton *random, *invert;
    QLabel *txt;


};

#endif // PLOTHISTO_H
