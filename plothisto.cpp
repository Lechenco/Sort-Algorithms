#include "plothisto.h"
#include "msort.cpp"
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
        set0 = new QBarSet("Quick");

        //Iniciando variaveis e vetor inicial (invertido)
        for(int i = n; i > 0; i--){
            set0->append(i);
        }

        do{
            h = 3*h + 1;
        }while(h < 50);
        i = n;

        //Configurando o plot
        series = new QBarSeries(this);
        series->append(set0);


        chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Shellsort");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        chart->legend()->setVisible(false);
        /*chart->legend()->setAlignment(Qt::AlignBottom);*/

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(640, 480);

        botaum = new QPushButton(this);
        botaum->setText("Random");

        //Conta o numero de iteraçoes necessarias para ordenar a entrada
        txt = new QLabel();
        txt->setNum(count);

        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(botaum, 1, 0);
        mainLayout->addWidget(txt, 0, 0);
        mainLayout->addWidget(chartView, 1, 1);
        setLayout(mainLayout);

        //chartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        //Timer que atualiza o indice h
        updateTimer = new QTimer(this);
        updateTimer->setInterval(150);
        updateTimer->start();


//        mergeSort(vet, 0, n -1);
        //Conecçoes
        connect(updateTimer, SIGNAL (timeout()), this, SLOT (teste()));
        connect(botaum, SIGNAL (clicked(bool)), this, SLOT (BotaumEvent()));
}

//Slot que gera um novo vetor e reinicia o algoritmo
void PlotHisto::BotaumEvent(){
    for(int i = 0; i < n; i++){
        set0->replace(i, aleatorio());
    }
    do{
        h = 3*h + 1;
    }while(h < 50);
    i = n;

    count = 0;
    updateTimer->start();


}

//Slot que gerencia os indices da funçao shellsort
void PlotHisto::teste(){
     if(i >= n){
        h /= 3;
        i = h;
     }

     this->shellsort();
     count++;
     txt->setNum(count);

     if(h ==1 && i >= n)
         updateTimer->stop();

}

void PlotHisto::shellsort(){
     chave = set0->at(i);
     j = i;
     while(j >= h && set0->at(j - h) > chave){
         set0->replace(j, set0->at(j - h));
         j -= h;
     }

     set0->replace(j, chave);
     updateTimer->start();

     i++;
}
