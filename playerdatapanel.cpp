#include "playerdatapanel.h"
#include "./ui_playerdatapanel.h"

PlayerDataPanel::PlayerDataPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerDataPanel)
{
    ui->setupUi(this);
}

PlayerDataPanel::~PlayerDataPanel()
{
    delete ui;
}
