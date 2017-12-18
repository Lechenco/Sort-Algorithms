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

        s->setSet(set0);
        m->setSet(set1);
        b->setSet(set2);
        q->setSet(set3);
        is->setSet(set4);
        ss->setSet(set5);
        r->setSet(set6);

        resetRand();

        r->setN(n);
        //Iniciando variaveis e vetor inicial (invertido)
        for(int i = n, j = 0; i > 0; i--, j++){
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
        random->setFixedSize(100, 30);

        invert = new QPushButton(this);
        invert->setText("Invertido");
        invert->setFixedSize(100, 30);

        play = new QPushButton(this);
        play->setText("Play");
        play->setFixedSize(100, 30);

        almost = new QPushButton(this);
        almost->setFixedSize(100, 30);
        almost->setText("Quase ord.");

        exitb = new QPushButton(this);
        exitb->setText("Sair");
        exitb->setFixedSize(100, 30);

        slider = new QSlider();
        slider->setOrientation(Qt::Horizontal);
        slider->setFixedSize(200, 40);
        slider->setRange(5, 70);
        slider->setValue(n);

        nStatus = new QLabel();
        nStatus->setText("n:  " + QString::number(n));
        nStatus->setFixedSize(100, 30);
        nStatus->setAlignment(Qt::AlignRight);

        //===========================================
        //Graficos
        //============================================

        baseLayout = new QGridLayout();
        QHBoxLayout *settingsLayout = new QHBoxLayout();

        QHBoxLayout *auxLayout = new QHBoxLayout();
        settingsLayout->setDirection(QHBoxLayout::TopToBottom);
        auxLayout->addWidget(random);
        auxLayout->addWidget(invert);
        settingsLayout->addLayout(auxLayout);

        auxLayout = new QHBoxLayout();
        auxLayout->addWidget(almost);
        auxLayout->addWidget(play);
        settingsLayout->addLayout(auxLayout);

        auxLayout = new QHBoxLayout();
        auxLayout->addWidget(nStatus);

        auxLayout->addWidget(slider);
        settingsLayout->addLayout(auxLayout);

        //settingsLayout->addWidget(slider);
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
        m->moveToThread(&workerthread);
        connect(&workerthread, &QThread::finished, m, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, m, &Merge::doWork);
        connect(m, &Merge::resultReady, this, &PlotHisto::updateChart);
        connect(m, &Merge::greenPeace, this, &PlotHisto::isRunning);

//ShellSort ThreadConnection
        s->moveToThread(&worker2);
        connect(&worker2, &QThread::finished, s, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, s, &ShellSort::doWork);
        connect(s, &ShellSort::resultReady, this, &PlotHisto::updateChart);
        connect(s, &ShellSort::greenPeace, this, &PlotHisto::isRunning);

//BubbleSort ThreadConnection
        b->moveToThread(&workerB);
        connect(&workerB, &QThread::finished, b, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, b, &BubbleSort::doWork);
        connect(b, &BubbleSort::resultReady, this, &PlotHisto::updateChart);
        connect(b, &BubbleSort::greenPeace, this, &PlotHisto::isRunning);

//QuickSort ThreadConnection
        q->moveToThread(&workerQ);
        connect(&workerQ, &QThread::finished, q, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, q, &QuickSort::doWork);
        connect(q, &QuickSort::resultReady, this, &PlotHisto::updateChart);
        connect(q, &QuickSort::greenPeace, this, &PlotHisto::isRunning);

 //InsetionSort ThreadConnection
        is->moveToThread(&workerI);
        connect(&workerI, &QThread::finished, is, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, is, &InsertionSort::doWork);
        connect(is, &InsertionSort::resultReady, this, &PlotHisto::updateChart);
        connect(is, &InsertionSort::greenPeace, this, &PlotHisto::isRunning);

//SelectionSort ThreadConnection
      //  ss->setN(n);
        ss->moveToThread(&workerSS);
        connect(&workerSS, &QThread::finished, ss, &QObject::deleteLater);
        connect(this, &PlotHisto::operate, ss, &SelectionSort::doWork);
        connect(ss, &SelectionSort::resultReady, this, &PlotHisto::updateChart);
        connect(ss, &SelectionSort::greenPeace, this, &PlotHisto::isRunning);

//RadixSort ThreadConnection
         r->moveToThread(&workerR);
         connect(&workerR, &QThread::finished, r, &QObject::deleteLater);
         connect(this, &PlotHisto::operate, r, &RadixSort::doWork);
         connect(r, &RadixSort::resultReady, this, &PlotHisto::updateChart);
         connect(r, &RadixSort::greenPeace, this, &PlotHisto::isRunning);

        workerthread.start();
        worker2.start();
        workerB.start();
        workerQ.start();
        workerI.start();
        workerSS.start();
        workerR.start();

        //Conecçoes
        connect(random, SIGNAL (clicked(bool)), this, SLOT (randomArray()));
        connect(invert, SIGNAL (clicked(bool)), this, SLOT (invertArray()));
        connect(slider, SIGNAL (valueChanged(int)), this, SLOT (setN(int)));
        connect(play,   SIGNAL (clicked(bool)), this, SLOT (startThreads()));
        connect(almost, SIGNAL (clicked(bool)), this, SLOT (almostArray()));
        connect(exitb, SIGNAL (clicked(bool)), this, SLOT (finishApp()));
}

void PlotHisto::finishApp(){
    exit(0);
}

void PlotHisto::startThreads(){
    count = 0;
    slider->setEnabled(false);

    emit operate();
}

void PlotHisto::setN(int n){

    set2->remove(0, this->n);
    set0->remove(0, this->n -1);
    set1->remove(0, this->n);
    set3->remove(0, this->n);
    set4->remove(0, this->n);
    set5->remove(0, this->n);
    set6->remove(0, this->n);
    this->n = n;
    nStatus->setText("n:  " + QString::number(n));
    r->setN(n);

    play->setEnabled(false);
    random->setEnabled(true);
    almost->setEnabled(true);
    invert->setEnabled(true);

}

void PlotHisto::almostArray(){
    for(int j = 1, i=0; j <= n; j++ ){
        if(j%5==0){
          i=j+5;
          if(i>=n){
             i=n;
          }
          set0->append(i);
          set1->append(i);
          set2->append(i);
          set3->append(i);
          set4->append(i);
          set5->append(i);
          set6->append(i);
        }else{
          set0->append(j);
          set1->append(j);
          set2->append(j);
          set3->append(j);
          set4->append(j);
          set5->append(j);
          set6->append(j);
        }

    }
    this->updateArrays();
    for(int i = m_chartView.size(); i >= 0; i--)
      m_chartView.removeAt(i);

    this->createChart();

    play->setEnabled(true);
    random->setEnabled(false);
    almost->setEnabled(false);
    invert->setEnabled(false);
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

    play->setEnabled(true);
    random->setEnabled(false);
    almost->setEnabled(false);
    invert->setEnabled(false);

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

    play->setEnabled(true);
    random->setEnabled(false);
    almost->setEnabled(false);
    invert->setEnabled(false);
}

void PlotHisto::updateChart(){
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

void PlotHisto::isRunning(int x){
    count++;
 /*
    switch(x){
        case 0:
             set0->setColor(Qt::green);
             break;
       case 1:
            set1->setColor(Qt::green);
            break;
        case 2:
            set2->setColor(Qt::green);
            break;
        case 3:
            set3->setColor(Qt::green);
            break;
        case 4:
            set4->setColor(Qt::green);
            break;
        case 5:
            set5->setColor(Qt::green);
            break;
        case 6:
            set6->setColor(Qt::green);
            break;

    }

 */
    if(count % 7 == 0){
        slider->setEnabled(true);

        QTime *tmp = new QTime();
        tmp->start();
        while(tmp->elapsed() < 200){

        }

    }
}
