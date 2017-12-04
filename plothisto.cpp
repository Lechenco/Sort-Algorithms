#include "bubblesort.h"
#include "insertionsort.h"
#include "merge.h"
#include "shellsort.h"
#include "selectionsort.h"
#include "quicksort.h"
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
        b = new BubbleSort();
        is = new InsertionSort();
        m = new Merge();
        s = new ShellSort();
        ss = new SelectionSort();
        q = new QuickSort();
        set0 = new QBarSet("Shell");
        set1 = new QBarSet("Merge");
        set2 = new QBarSet("Bubble");
        set3 = new QBarSet("Quick");
        set4 = new QBarSet("Insert");
        set5 = new QBarSet("Selection");

        //Iniciando variaveis e vetor inicial (invertido)
        for(int i = n, j = 0; i > 0; i--, j++){
            b->A[j] = i;
            is->A[j] = i;
            s->A[j] = i;
            ss->A[j] = i;
            m->A[j] = i;
            q->A[j] = i;

            set0->append(i);
            set1->append(i);
            set2->append(i);
            set3->append(i);
            set4->append(i);
            set5->append(i);
        }

        random = new QPushButton(this);
        random->setText("Random");
        random->setFixedSize(60, 30);

        invert = new QPushButton(this);
        invert->setText("Invertido");
        invert->setFixedSize(60, 30);


        //===========================================
        //Graficos
        //============================================

        QGridLayout *baseLayout = new QGridLayout();
        QHBoxLayout *settingsLayout = new QHBoxLayout();
        settingsLayout->addWidget(random);
        settingsLayout->addWidget(invert);
        baseLayout->addLayout(settingsLayout, 0, 0);

        QChartView *chartView = new QChartView(this->addChart(0));
        baseLayout->addWidget(chartView, 0, 2);
        m_chartView << chartView;

        chartView = new QChartView(this->addChart(1));
        baseLayout->addWidget(chartView, 1, 0);
        m_chartView << chartView;

        chartView = new QChartView(this->addChart(2));
        baseLayout->addWidget(chartView, 1, 1);
        m_chartView << chartView;

        chartView = new QChartView(this->addChart(3));
        baseLayout->addWidget(chartView, 1, 2);
        m_chartView << chartView;

        chartView = new QChartView(this->addChart(4));
        baseLayout->addWidget(chartView, 2, 0);
        m_chartView << chartView;

        chartView = new QChartView(this->addChart(5));
        baseLayout->addWidget(chartView, 2, 1);
        m_chartView << chartView;

        setLayout(baseLayout);


        //chartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


//Merge Sort ThreadConnection

        m->setN(n);
        m->moveToThread(&workerthread);
        connect(&workerthread, &QThread::finished, m, &QObject::deleteLater);
       // connect(&workerthread, &QThread::finished, this, &PlotHisto::updateColor);
        connect(this, &PlotHisto::operate, m, &Merge::doWork);
        connect(m, &Merge::resultReady, this, &PlotHisto::updateChart);

//ShellSort ThreadConnection
        s->setN(n);
        s->moveToThread(&worker2);
        connect(&worker2, &QThread::finished, s, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, s, &ShellSort::doWork);
        connect(s, &ShellSort::resultReady, this, &PlotHisto::updateChart);

//BubbleSort ThreadConnection
        b->setN(n);
        b->moveToThread(&workerB);
        connect(&workerB, &QThread::finished, b, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, b, &BubbleSort::doWork);
        connect(b, &BubbleSort::resultReady, this, &PlotHisto::updateChart);

//QuickSort ThreadConnection
        q->setN(n);
        q->moveToThread(&workerQ);
        connect(&workerQ, &QThread::finished, q, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, q, &QuickSort::doWork);
        connect(q, &QuickSort::resultReady, this, &PlotHisto::updateChart);

 //InsetionSort ThreadConnection
        is->setN(n);
        is->moveToThread(&workerI);
        connect(&workerI, &QThread::finished, is, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, is, &InsertionSort::doWork);
        connect(is, &InsertionSort::resultReady, this, &PlotHisto::updateChart);

//SelectionSort ThreadConnection
        ss->setN(n);
        ss->moveToThread(&workerSS);
        connect(&workerSS, &QThread::finished, ss, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, ss, &SelectionSort::doWork);
        connect(ss, &SelectionSort::resultReady, this, &PlotHisto::updateChart);

        workerthread.start();
        worker2.start();
        workerB.start();
        workerQ.start();
        workerI.start();
        workerSS.start();

       emit operate();

        //Conecçoes
        connect(random, SIGNAL (clicked(bool)), this, SLOT (randomArray()));
        connect(invert, SIGNAL (clicked(bool)), this, SLOT (invertArray()));
}

//Slot que gera um novo vetor e reinicia o algoritmo
void PlotHisto::randomArray(){
    int aux;

    for(int i = 0; i < n; i++){
        aux = aleatorio(n);
        set0->replace(i, aux);
        set1->replace(i, aux);
        set2->replace(i, aux);
        set3->replace(i, aux);
        set4->replace(i, aux);
        set5->replace(i, aux);
    }
    this->updateArrays();
    emit operate();

}

void PlotHisto::invertArray(){
    for(int i = n, j = 0; j < n; i--, j++ ){
        set0->replace(j, i);
        set1->replace(j, i);
        set2->replace(j, i);
        set3->replace(j, i);
        set4->replace(j, i);
        set5->replace(j, i);
    }
    this->updateArrays();

    emit operate();

}

void PlotHisto::updateChart(){
    for(int i = 0; i < n; i++){
        set0->replace(i, s->A[i]);
        set1->replace(i, m->A[i]);
        set2->replace(i, b->A[i]);
        set3->replace(i, q->A[i]);
        set4->replace(i, is->A[i]);
        set5->replace(i, is->A[i]);
    }
}

void PlotHisto::updateArrays(){
    for(int i = 0; i < n; i++){
        b->A[i] = set0->at(i);
        m->A[i] = set0->at(i);
        s->A[i] = set0->at(i);
        q->A[i] = set0->at(i);
        is->A[i] = set0->at(i);
        ss->A[i] = set0->at(i);
    }

}

QChart* PlotHisto::addChart(int i){
    //Configurando o plot
    QBarSeries *series = new QBarSeries(this);
    QChart *chart = new QChart();

    switch (i) {
    case 0:
        series->append(set0);
        chart->setTitle("Shellsort");
        break;
    case 1:
        series->append(set1);
        chart->setTitle("MergeSort");
        break;
    case 2:
        series->append(set2);
        chart->setTitle("BubbleSort");
        break;
    case 3:
        series->append(set3);
        chart->setTitle("QuickSort");
        break;
    case 4:
        series->append(set4);
        chart->setTitle("InsertionSort");
        break;
    case 5:
        series->append(set5);
        chart->setTitle("SelectionSort");
        break;
    default:
        break;
    }


    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setVisible(false);
    /*chart->legend()->setAlignment(Qt::AlignBottom);*/
    return chart;
}

void PlotHisto::updateColor(){
    //QColor *color = new QColor(Qt::green);

    //if(workerthread.isFinished())
        set1->setColor(Qt::green);
        m_chartView.at(1)->chart()->setTitle("Olar");


}
