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
class RadixSort;
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
    QThread workerR;
    QThread workerSS;
    QThread workerQ;
public:
    explicit PlotHisto(QWidget *parent = nullptr);


public slots:
    //void handleResults();
    void randomArray();
    void invertArray();
    void updateChart();
    void setN(int n);
    void startThreads();

signals:
    void operate();

private:
     BubbleSort *b;
     InsertionSort *is;
     Merge *m;
     RadixSort *r;
     ShellSort *s;
     SelectionSort *ss;
     QuickSort *q;

    int n = TAM, count = 0;

    QBarSet *set0, *set1, *set2, *set3, *set4, *set5, *set6;
    QList<QChartView *> m_chartView;
    QList<QLabel *> m_label, m_compara;
    QPushButton *random, *invert, *play;
    QSlider *slider;
    QGridLayout *baseLayout;

    QChart* addChart(int i);
    void updateArrays();
    void createChart();


};

#endif // PLOTHISTO_H
