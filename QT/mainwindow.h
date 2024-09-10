#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/qwidget.h>
#include "curveplotfifo.h"
#include "realtimecurveplot.h"
#include <QtCore/QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(double _minY, double _maxY, int CURVE_CHANNEL_COUNT,QWidget *parent = nullptr);
    ~MainWindow();

    CurvePlotFifo* GetFIFO()
    {
        return fifo;
    }

private:
    Ui::MainWindow *ui;
    CurvePlotFifo* fifo;
    QThread generatorThread;
    RealtimeCurvePlot* plot;
};
#endif // MAINWINDOW_H
