#include "bubblesort.h"
#include "insertionsort.h"
#include "merge.h"
#include "radixsort.h"
#include "shellsort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include "plothisto.h"
#include "random.cpp"

#include <string>
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
        r = new RadixSort();
        s = new ShellSort();
        ss = new SelectionSort();
        q = new QuickSort();
        set0 = new QBarSet("Shell");
        set1 = new QBarSet("Merge");
        set2 = new QBarSet("Bubble");
        set3 = new QBarSet("Quick");
        set4 = new QBarSet("Insert");
        set5 = new QBarSet("Selection");
        set6 = new QBarSet("Radix");

        resetRand();
        b->setN(n);
        is->setN(n);
        s->setN(n);
        ss->setN(n);
        m->setN(n);
        q->setN(n);
        r->setN(n);
        //Iniciando variaveis e vetor inicial (invertido)
        for(int i = n, j = 0; i > 0; i--, j++){
            b->A[j] = i;
            is->A[j] = i;
            s->A[j] = i;
            ss->A[j] = i;
            m->A[j] = i;
            q->A[j] = i;
            r->A[j] = i;

            set0->append(i);
            set1->append(i);
            set2->append(i);
            set3->append(i);
            set4->append(i);
            set5->append(i);
            set6->append(i);
        }

        random = new QPushButton(this);
        random->setText("Random");
        random->setFixedSize(120, 30);

        invert = new QPushButton(this);
        invert->setText("Invertido");
        invert->setFixedSize(120, 30);

        play = new QPushButton(this);
        play->setText("Play");
        play->setFixedSize(120, 30);


        slider = new QSlider();
        slider->setOrientation(Qt::Horizontal);
        slider->setFixedSize(300, 30);
        slider->setRange(5, 70);

        //===========================================
        //Graficos
        //============================================

        baseLayout = new QGridLayout();
        QHBoxLayout *settingsLayout = new QHBoxLayout();
        settingsLayout->setDirection(QHBoxLayout::TopToBottom);
        settingsLayout->addWidget(random);
        settingsLayout->addWidget(invert);
        settingsLayout->addWidget(play);
        settingsLayout->addWidget(slider);
        baseLayout->addLayout(settingsLayout, 0, 0);

        this->createChart();

        QHBoxLayout *textLayout = new QHBoxLayout();
        QBoxLayout * numLayout = new QHBoxLayout();
        textLayout->setDirection(QBoxLayout::TopToBottom);
        numLayout->setDirection(QBoxLayout::TopToBottom);

        QLabel *aux = new QLabel("");
        textLayout->addWidget(aux);
        aux = new QLabel("Comp. \tSwap");
        numLayout->addWidget(aux);
        for(int i = 0; i < m_label.size(); i++){
            textLayout->addWidget(m_label.at(i));
            numLayout->addWidget(m_compara.at(i));
        }
        baseLayout->addLayout(textLayout, 0, 1);
        baseLayout->addLayout(numLayout, 0, 1,Qt::AlignRight);
        setLayout(baseLayout);


        //chartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


//Merge Sort ThreadConnection

        //m->setN(n);
        m->moveToThread(&workerthread);
        connect(&workerthread, &QThread::finished, m, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, m, &Merge::doWork);
        connect(m, &Merge::resultReady, this, &PlotHisto::updateChart);

//ShellSort ThreadConnection
      //  s->setN(n);
        s->moveToThread(&worker2);
        connect(&worker2, &QThread::finished, s, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, s, &ShellSort::doWork);
        connect(s, &ShellSort::resultReady, this, &PlotHisto::updateChart);

//BubbleSort ThreadConnection
        //b->setN(n);
        b->moveToThread(&workerB);
        connect(&workerB, &QThread::finished, b, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, b, &BubbleSort::doWork);
        connect(b, &BubbleSort::resultReady, this, &PlotHisto::updateChart);

//QuickSort ThreadConnection
       // q->setN(n);
        q->moveToThread(&workerQ);
        connect(&workerQ, &QThread::finished, q, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, q, &QuickSort::doWork);
        connect(q, &QuickSort::resultReady, this, &PlotHisto::updateChart);

 //InsetionSort ThreadConnection
       // is->setN(n);
        is->moveToThread(&workerI);
        connect(&workerI, &QThread::finished, is, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, is, &InsertionSort::doWork);
        connect(is, &InsertionSort::resultReady, this, &PlotHisto::updateChart);

//SelectionSort ThreadConnection
      //  ss->setN(n);
        ss->moveToThread(&workerSS);
        connect(&workerSS, &QThread::finished, ss, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, ss, &SelectionSort::doWork);
        connect(ss, &SelectionSort::resultReady, this, &PlotHisto::updateChart);

//RadixSort ThreadConnection
      //   r->setN(n);
         r->moveToThread(&workerR);
         connect(&workerR, &QThread::finished, r, &QObject::deleteLater);
         connect(this, &PlotHisto::operate, r, &RadixSort::doWork);
         connect(r, &RadixSort::resultReady, this, &PlotHisto::updateChart);

        workerthread.start();
        worker2.start();
        workerB.start();
        workerQ.start();
        workerI.start();
        workerSS.start();
        workerR.start();

       //emit operate();

        //Conecçoes
        connect(random, SIGNAL (clicked(bool)), this, SLOT (randomArray()));
        connect(invert, SIGNAL (clicked(bool)), this, SLOT (invertArray()));
        connect(slider, SIGNAL (valueChanged(int)), this, SLOT (setN(int)));
        connect(play,   SIGNAL (clicked(bool)), this, SLOT (startThreads()));
}

void PlotHisto::startThreads(){
    emit operate();
}

void PlotHisto::setN(int n){
    set2->remove(0, this->n);
    set0->remove(0, this->n);
    set1->remove(0, this->n);
    set3->remove(0, this->n);
    set4->remove(0, this->n);
    set5->remove(0, this->n);
    set6->remove(0, this->n);
    this->n = n;
    b->setN(n);
    q->setN(n);
    ss->setN(n);
    s->setN(n);
    is->setN(n);
    r->setN(n);
    m->setN(n);

}

//Slot que gera um novo vetor e reinicia o algoritmo
void PlotHisto::randomArray(){
    int aux;

    for(int i = 0; i < n; i++){
        aux = aleatorio(n);
        set0->append(aux);
        set1->append(aux);
        set2->append(aux);
        set3->append(aux);
        set4->append(aux);
        set5->append(aux);
        set6->append(aux);
    }
    this->updateArrays();
    for(int i = m_chartView.size(); i >= 0; i--)
        m_chartView.removeAt(i);

    this->createChart();
    //emit operate();

}

void PlotHisto::invertArray(){
    for(int i = n, j = 0; j < n; i--, j++ ){
        set0->append(i);
        set1->append(i);
        set2->append(i);
        set3->append(i);
        set4->append(i);
        set5->append(i);
        set6->append(i);
    }
    this->updateArrays();
    for(int i = m_chartView.size(); i >= 0; i--)
        m_chartView.removeAt(i);

    this->createChart();

    //emit operate();

}

void PlotHisto::updateChart(){
    for(int i = 0; i < n; i++){
        set0->replace(i, s->A[i]);
        set1->replace(i, m->A[i]);
        set2->replace(i, b->A[i]);
        set3->replace(i, q->A[i]);
        set4->replace(i, is->A[i]);
        set5->replace(i, ss->A[i]);
        set6->replace(i, r->A[i]);
    }
    m_compara.at(0)->setText(QString::number(s->comp) + " \t" + QString::number(s->swap));
    m_compara.at(1)->setText(QString::number(m->swap) + " \t" + QString::number(m->swap));
    m_compara.at(2)->setText(QString::number(b->comp) + " \t" + QString::number(b->swap));
    m_compara.at(3)->setText(QString::number(q->comp) + " \t" + QString::number(q->swap));
    m_compara.at(4)->setText(QString::number(is->comp) + " \t" + QString::number(is->swap));
    m_compara.at(5)->setText(QString::number(ss->comp) + " \t" + QString::number(ss->swap));
    m_compara.at(6)->setText(QString::number(r->comp) + " \t" + QString::number(r->swap));
}

void PlotHisto::updateArrays(){
    for(int i = 0; i < n; i++){
        b->A[i] = set0->at(i);
        m->A[i] = set0->at(i);
        s->A[i] = set0->at(i);
        q->A[i] = set0->at(i);
        is->A[i] = set0->at(i);
        ss->A[i] = set0->at(i);
        r->A[i] = set0->at(i);
    }

}

QChart* PlotHisto::addChart(int i){
    //Configurando o plot
    QBarSeries *series = new QBarSeries(this);
    QChart *chart = new QChart();
    QLabel *label = new QLabel();
    QLabel *numLabel = new QLabel();

    switch (i) {
    case 0:
        series->append(set0);
        chart->setTitle("Shellsort");
        label->setText("ShellSort");
        break;
    case 1:
        series->append(set1);
        chart->setTitle("MergeSort");
        label->setText("MergeSort");
        break;
    case 2:
        series->append(set2);
        chart->setTitle("BubbleSort");
        label->setText("BubbleSort");
        break;
    case 3:
        series->append(set3);
        chart->setTitle("QuickSort");
        label->setText("QuickSort");
        break;
    case 4:
        series->append(set4);
        chart->setTitle("InsertionSort");
        label->setText("InsertionSort");
        break;
    case 5:
        series->append(set5);
        chart->setTitle("SelectionSort");
        label->setText("SelectionSort");
        break;
    case 6:
        series->append(set6);
        chart->setTitle("RadixSort");
        label->setText("RadixSort");
        break;
    default:
        break;
    }
    numLabel->setNum(0);

    m_compara << numLabel;
    m_label << label;

    chart->addSeries(series);

   // chart->setAnimationOptions(QChart::SeriesAnimations);

    //chart->setAnimationOptions(QChart::SeriesAnimations);


    chart->legend()->setVisible(false);
    /*chart->legend()->setAlignment(Qt::AlignBottom);*/
    return chart;
}

void PlotHisto::createChart(){
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

    chartView = new QChartView(this->addChart(6));
    baseLayout->addWidget(chartView, 2, 2);
    m_chartView << chartView;
}
