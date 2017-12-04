#ifndef PLOTHISTO_H
#define PLOTHISTO_H
#define TAM 30

#include <QWidget>
#include <QtCharts>
#include <QThread>

class QPushButton;
class QLabel;

class BubbleSort;
class InsertionSort;
class Merge;
class SelectionSort;
class ShellSort;
class QuickSort;

class PlotHisto : public QWidget
{
    Q_OBJECT
    QThread workerthread;
    QThread worker2;
    QThread workerB;
    QThread workerI;
    QThread workerSS;
    QThread workerQ;
public:
    explicit PlotHisto(QWidget *parent = nullptr);
    void updateArrays();

public slots:
    //void handleResults();
    void randomArray();
    void invertArray();
    void updateChart();
    void updateColor();


signals:
    void operate();

private:
     BubbleSort *b;
     InsertionSort *is;
     Merge *m;
     ShellSort *s;
     SelectionSort *ss;
     QuickSort *q;

    int n = TAM, count = 0;

    QBarSet *set0, *set1, *set2, *set3, *set4, *set5;
    QList<QChartView *> m_chartView;
    QPushButton *random, *invert;

    QChart* addChart(int i);


};

#endif // PLOTHISTO_H
