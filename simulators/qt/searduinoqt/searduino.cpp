#include "searduino.h"
#include "ui_searduino.h"

Searduino::Searduino(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Searduino)
{
    ui->setupUi(this);
}

Searduino::~Searduino()
{
    delete ui;
}
