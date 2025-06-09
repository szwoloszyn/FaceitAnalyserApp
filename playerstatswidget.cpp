#include "playerstatswidget.h"
#include "ui_playerstatswidget.h"

PlayerStatsWidget::PlayerStatsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerStatsWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->empty);

    connect (this->ui->input, &PlayerInputPanel::confirmed, this, &PlayerStatsWidget::requestData);
}

PlayerStatsWidget::~PlayerStatsWidget()
{
    delete ui;
}

void PlayerStatsWidget::setData(Player *player)
{
    ui->stackedWidget->setCurrentWidget(ui->data);
}

void PlayerStatsWidget::setInvalidNickname()
{
    ui->stackedWidget->setCurrentWidget(ui->invalidCnt);
}

void PlayerStatsWidget::requestData(bool isLast50)
{
    emit dataRequested(isLast50);
}
