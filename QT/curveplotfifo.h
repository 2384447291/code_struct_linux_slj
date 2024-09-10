#ifndef CURVEPLOTFIFO_H
#define CURVEPLOTFIFO_H

#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QMutex>
#include <QtCore/QQueue>

//QObject是Qt框架中的一个基类，用于提供对象树、信号和槽机制、事件处理等功能。
//它是Qt中所有对象的基类，使得对象能够具有父子关系、信号和槽通信，以及事件处理能力。
//QObject还提供了内存管理和对象生命周期管理的功能，使得对象能够在合适的时候被销毁，从而避免内存泄漏问题。
class CurvePlotFifo : QObject
{
    Q_OBJECT
public:
    CurvePlotFifo(int capacity);
    QVector<double> read();
    void write(QVector<double> data);
    bool isEmpty() const;
    bool isFull() const;
    void clear();

private:
    int capacity;
    mutable QMutex mutex;
    QQueue<QVector<double>> buffer;
};

#endif 
