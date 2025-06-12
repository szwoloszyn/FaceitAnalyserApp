#include "matchstatswidget.h"
#include "ui_matchstatswidget.h"

MatchStatsWidget::MatchStatsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchStatsWidget)
{
    ui->setupUi(this);
    ui->input->show();
    ui->stackedWidget->setCurrentWidget(ui->empty);

    connect(ui->input, &MatchInputPanel::confirmed, this, &MatchStatsWidget::requestData);
}

MatchStatsWidget::~MatchStatsWidget()
{
    delete ui;
}

void MatchStatsWidget::setData(const MatchStats &match)
{
    ui->stackedWidget->setCurrentWidget(ui->data);
    ui->data->setData(match);
}

void MatchStatsWidget::setCustomError(const QString &error)
{
    ui->invalid->setAlignment(Qt::AlignLeft);
    ui->invalid->setText(error);
    ui->stackedWidget->setCurrentWidget(ui->invalidCnt);
}

void MatchStatsWidget::setErrorFromPlayer()
{
    ui->invalid->setAlignment(Qt::AlignLeft);
    ui->invalid->setText("input valid nickname first");
    ui->stackedWidget->setCurrentWidget(ui->invalidCnt);
}

void MatchStatsWidget::requestData(const QString &match_id)
{
    ui->stackedWidget->setCurrentWidget(ui->empty);
    emit dataRequested(match_id);
}
