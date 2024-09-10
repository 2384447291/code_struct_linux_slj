#include "mainwindow.h"
#include "./ui_mainwindow.h"//在编译后自动生成由mainwindow.ui

MainWindow::MainWindow(double _minY, double _maxY, int CURVE_CHANNEL_COUNT, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 初始化缓冲区
    fifo = new CurvePlotFifo(1024);
    // 初始化曲线控件
    plot = new RealtimeCurvePlot(_minY, _maxY, fifo, (int)CURVE_CHANNEL_COUNT);

    this->setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


