#ifndef PLOTHISTO_H
#define PLOTHISTO_H

#include <QWidget>
#include <QtCharts>

class QPushButton;
class QLabel;
//class ShellSort;
class PlotHisto : public QWidget
{
    Q_OBJECT
public:
    explicit PlotHisto(QWidget *parent = nullptr);

private slots:
    void teste();
    void BotaumEvent();
    void shellsort();
signals:

public slots:
private:


    int vet[50];
    int chave, i, j, n = 50, count = 0;
    int h = 1;
    QTimer *updateTimer;
    QBarSet *set0;
    QBarSeries *series;
    QChart *chart;
    QChartView *chartView;
    QPushButton *botaum;
    QLabel *txt;

    //ShellSort *ssort;
};

#endif // PLOTHISTO_H
