#include "boosttestwin.h"
#include "./ui_boosttestwin.h"

BoostTestWin::BoostTestWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BoostTestWin)
{
    ui->setupUi(this);
}

BoostTestWin::~BoostTestWin()
{
    delete ui;
}

