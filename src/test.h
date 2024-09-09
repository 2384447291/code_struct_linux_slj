#pragma once
#include "ui_test.h"
#include <QMainWindow>

class test : public QMainWindow {
    Q_OBJECT
    
public:
    test(QWidget* parent = nullptr);
    ~test();

private:
    Ui_test* ui;
};