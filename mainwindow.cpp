#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QTimer>

#define GLOB_C 60

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*plot = new SignalPlot(ui->centralWidget);
    ui->verticalLayout->addWidget(plot);
    plot->setChannels(4);
    plot->setFrequency(250);
    plot->setTimeInterval(2);
    plot->setAmplification(1);
    plot->resize(500,500);*/

    zone = new PlCurvesZone(ui->centralWidget);
    zone->reconfigure(GLOB_C,1000);
    zone->resize(100,100);
    ui->verticalLayout->addWidget(zone);

    /*QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newData()));
    timer->start(4);*/
    this->startTimer(4*8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent*)
{
    const int c = GLOB_C;
    const int a = 5;
    qreal data[c*8];
    for(int i=0; i<c*8; i+=c)
    {
        for(int j=0; j<c; ++j)
            data[i+j] = a*sin(t * 2*M_PI*(j+1)/(250-1));

        t++;
    }
    //plot->addData(data, 4*8);
    zone->addData(data, c*8);
}

void MainWindow::on_pushButton_clicked()
{
   /* t=0;
    for(int i=0; i<500; ++i)
    {
        qreal data[4];
        data[0] = 50*sin(i * 2*M_PI*1/(250-1));
        data[1] = 50*sin(i * 2*M_PI*2/(250-1));
        data[2] = 50*sin(i * 2*M_PI*4/(250-1));
        data[3] = 50*sin(i * 2*M_PI*8/(250-1));
        zone->addData(data, 4);
    }*/
}

void MainWindow::on_pushButton_3_clicked()
{
    zone->reconfigure(GLOB_C, 1000);
}

void MainWindow::on_pushButton_2_clicked()
{
    zone->reconfigure(GLOB_C, 500);
}
