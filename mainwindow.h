#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <signalplot.h>
#include "plcurveszone.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //SignalPlot *plot;

    PlCurvesZone *zone;

    int t;

private:
    void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
