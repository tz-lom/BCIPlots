#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = new SignalPlot(ui->centralWidget);
    ui->verticalLayout->addWidget(plot);
    plot->setChannels(4);
    plot->setFrequency(250);
    plot->setTimeInterval(2);
    plot->setAmplification(1);
    plot->resize(500,500);

    t=0;
    /*for(int i=0; i<500; ++i)
    {
        QVector<int> data;
        data.resize(4);
        data[0] = 50*sin(i * 2*M_PI*1/(250-1));
        data[1] = 50*sin(i * 2*M_PI*2/(250-1));
        data[2] = 50*sin(i * 2*M_PI*4/(250-1));
        data[3] = 50*sin(i * 2*M_PI*8/(250-1));
        plot->addData(data);
    }*/

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
    int data[4*8];
    for(int i=0; i<4*8; i+=4)
    {
        data[i+0] = 50*sin(t * 2*M_PI*1/(250-1));
        data[i+1] = 50*sin(t * 2*M_PI*2/(250-1));
        data[i+2] = 50*sin(t * 2*M_PI*4/(250-1));
        data[i+3] = 50*sin(t * 2*M_PI*8/(250-1));
        t++;
    }
    plot->addData(data, 4*8);
}
