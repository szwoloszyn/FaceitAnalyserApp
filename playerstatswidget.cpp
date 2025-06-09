#include "playerstatswidget.h"
#include "ui_playerstatswidget.h"

PlayerStatsWidget::PlayerStatsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerStatsWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->data);
}

PlayerStatsWidget::~PlayerStatsWidget()
{
    delete ui;
}
