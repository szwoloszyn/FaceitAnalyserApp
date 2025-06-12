#include "matchstatswidget.h"
#include "ui_matchstatswidget.h"

MatchStatsWidget::MatchStatsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchStatsWidget)
{
    ui->setupUi(this);
    ui->input->show();

    ui->stackedWidget->setCurrentWidget(ui->data);
}

MatchStatsWidget::~MatchStatsWidget()
{
    delete ui;
}
