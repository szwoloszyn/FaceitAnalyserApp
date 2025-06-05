#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

PlayerStatsWindow::PlayerStatsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerStatsWindow)
{
    ui->setupUi(this);
}

PlayerStatsWindow::~PlayerStatsWindow()
{
    delete ui;
}

