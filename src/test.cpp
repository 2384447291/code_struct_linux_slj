#include "test.h"

test::test(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_test)
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui; 
}