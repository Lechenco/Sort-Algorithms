#include "merge.h"
#include "shellsort.h"
#include "plothisto.h"
#include "random.cpp"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtWidgets/QGridLayout>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsView>


QT_CHARTS_USE_NAMESPACE

PlotHisto::PlotHisto(QWidget *parent) : QWidget(parent)
{
        m = new Merge();
        s = new ShellSort();
        set0 = new QBarSet("Quick");

        //Iniciando variaveis e vetor inicial (invertido)
        for(int i = n, j = 0; i > 0; i--, j++){
            s->A[j] = i;
            set0->append(i);
        }

        //Configurando o plot
        QBarSeries *series = new QBarSeries(this);
        series->append(set0);


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Shellsort");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        chart->legend()->setVisible(false);
        /*chart->legend()->setAlignment(Qt::AlignBottom);*/


        random = new QPushButton(this);
        random->setText("Random");
        random->setFixedSize(60, 30);

        invert = new QPushButton(this);
        invert->setText("Invertido");
        invert->setFixedSize(60, 30);


        //===========================================
        //TESTE
        //============================================

        QGridLayout *baseLayout = new QGridLayout();
        QHBoxLayout *settingsLayout = new QHBoxLayout();
        settingsLayout->addWidget(random);
        settingsLayout->addWidget(invert);
        baseLayout->addLayout(settingsLayout, 0, 0);

        QChartView *chartView = new QChartView(chart);
        baseLayout->addWidget(chartView, 1, 0);
        m_chartView << chartView;

        setLayout(baseLayout);


        //chartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


//Merge Sort ThreadConection
/*
        m->moveToThread(&workerthread);
        connect(&workerthread, &QThread::finished, m, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, m, &Merge::doWork);
        connect(m, &Merge::resultReady, this, &PlotHisto::BotaumEvent);
*/
        s->setN(n);
        s->moveToThread(&workerthread);
        connect(&workerthread, &QThread::finished, s, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, s, &ShellSort::doWork);
        connect(s, &ShellSort::resultReady, this, &PlotHisto::updateChart);

        workerthread.start();

        emit operate();

        //Conecçoes
        connect(random, SIGNAL (clicked(bool)), this, SLOT (randomArray()));
        connect(invert, SIGNAL (clicked(bool)), this, SLOT (invertArray()));
}

//Slot que gera um novo vetor e reinicia o algoritmo
void PlotHisto::randomArray(){

    for(int i = 0; i < n; i++){
        set0->replace(i, aleatorio(n));
    }
    this->updateArrays();
    emit operate();

}

void PlotHisto::invertArray(){
    for(int i = n, j = 0; j < n; i--, j++ )
        set0->replace(j, i);
    this->updateArrays();

    emit operate();

}

void PlotHisto::updateChart(){
    for(int i = 0; i < n; i++)
        set0->replace(i, s->A[i]);
}

void PlotHisto::updateArrays(){
    for(int i = 0; i < n; i++){
        m->A[i] = set0->at(i);
        s->A[i] = set0->at(i);
    }

}
