#ifndef REALTIMECURVEPLOT_H
#define REALTIMECURVEPLOT_H

#include <QtWidgets/QWidget>
#include "curveplotfifo.h"
#include "qcustomplot.h"

//QWidget是Qt框架中表示用户界面组件的基类。
//它是所有用户界面元素的基础，包括窗口、按钮、标签等。
//QWidget提供了绘制、事件处理、布局等功能，使得用户界面的创建和交互变得简单而灵活。
class RealtimeCurvePlot : public QWidget
{
    //Q_OBJECT这个宏必须在所有使用Qt信号和槽机制的类中定义。它使得Qt的元对象系统能够识别该类，并支持信号和槽的功能、动态属性、以及其他特性。
    Q_OBJECT
public:
    explicit RealtimeCurvePlot(double _minY, double _maxY, CurvePlotFifo* fifo, int channelCount, QWidget *parent = nullptr);
    //signals:是一个访问修饰符，用于声明信号。信号是Qt中用于对象间通信的机制，当某个事件发生时，信号会被发出，其他对象可以连接到这些信号以响应事件。
signals:
private:
    CurvePlotFifo* fifo;
    int channelCount;
    QCustomPlot* customPlot;
    QTimer replotTimer;
    QComboBox *displayLenthComboBox;
    int displayLengthInSecond = 8;
    double minY;
    double maxY;
private:
    void initLayout();
    void initCurvePlot();
    void initDisplayLengthComboBox();
    //private slots:是一个访问修饰符，用于声明槽函数。槽是响应信号的函数。当信号被发出时，连接到该信号的槽会被调用。`private`表示这些槽函数只能在类内部使用。
private slots:
    void refreshCurve();
    void onLegendClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);
    void onDisplayLengthChanged(int index);
};

#endif 
