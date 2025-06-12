#include "matchdatapanel.h"
#include "ui_matchdatapanel.h"

MatchDataPanel::MatchDataPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchDataPanel)
{
    ui->setupUi(this);
}

MatchDataPanel::~MatchDataPanel()
{
    delete ui;
}
