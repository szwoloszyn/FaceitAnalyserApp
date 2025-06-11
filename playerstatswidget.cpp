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

void PlayerStatsWidget::setData(const Player *player)
{
    ui->stackedWidget->setCurrentWidget(ui->data);
    ui->data->setData(player);
}

void PlayerStatsWidget::setErrorOnCall(const QString& error)
{
    ui->invalidLabel->setAlignment(Qt::AlignHCenter);
    ui->invalidLabel->setText(error);
    ui->stackedWidget->setCurrentWidget(ui->invalidCnt);
}

void PlayerStatsWidget::requestData(QString nickname, bool isLast50)
{
    ui->stackedWidget->setCurrentWidget(ui->empty);
    emit dataRequested(nickname, isLast50);
}
