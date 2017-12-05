#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <cstdlib>
#include <cstdio>
#include "plothisto.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    PlotHisto *chartView = new PlotHisto();

    window.setCentralWidget(chartView);
   // window.resize(800, 800);
    window.showFullScreen();


    return a.exec();

}

