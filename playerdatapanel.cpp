#include "playerdatapanel.h"
#include "./ui_playerdatapanel.h"

PlayerDataPanel::PlayerDataPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerDataPanel)
{
    ui->setupUi(this);
    ui->lvlProgress->setRange(100,2001);
}

PlayerDataPanel::~PlayerDataPanel()
{
    delete ui;
}

void PlayerDataPanel::setData(const Player *player)
{
    ui->ADR->setText(player->lifetime_stats.adr);
    ui->KDR->setText(player->lifetime_stats.kdr);
    ui->HLTV->setText(player->lifetime_stats.hltv);
    ui->elo->setText(player->acc_info.value("elo"));

    int elo = player->acc_info.value("elo").toInt();
    setUpProgressBar(elo);


}

void PlayerDataPanel::setUpProgressBar(int elo)
{
    if (elo > 2001) {
        elo = 2001;
    }
    ui->lvlProgress->setValue(elo);
}

void PlayerDataPanel::setUpProfilePicture(QString picture)
{

}
