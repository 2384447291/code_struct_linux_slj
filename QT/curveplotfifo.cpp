#include "curveplotfifo.h"
#include <QtCore/QMutexLocker>

CurvePlotFifo::CurvePlotFifo(int capacity) : capacity(capacity)
{
}

QVector<double> CurvePlotFifo::read()
{
    QMutexLocker locker(&mutex);
    if (!buffer.isEmpty())
    {
        return buffer.dequeue();
    }
    return {0};
}

void CurvePlotFifo::write(QVector<double> data)
{
    QMutexLocker locker(&mutex);
    if (buffer.size() < capacity)
    {
        buffer.enqueue(data);
    }
}

bool CurvePlotFifo::isEmpty() const
{
    QMutexLocker locker(&mutex);
    return buffer.isEmpty();
}

bool CurvePlotFifo::isFull() const
{
    QMutexLocker locker(&mutex);
    return buffer.size() > capacity;
}

void CurvePlotFifo::clear()
{
    QMutexLocker locker(&mutex);
    buffer.clear();
}
