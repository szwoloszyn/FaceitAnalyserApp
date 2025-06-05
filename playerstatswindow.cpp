#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

PlayerStatsWindow::PlayerStatsWindow(const QString& apiKey, QWidget *parent)
    : QWidget(parent)
    , client{new FaceitApiClient{apiKey}}
    , player{new Player}
    , lastResponse{QJsonObject()}
    , ui(new Ui::PlayerStatsWindow)
{
    ui->setupUi(this);
    connect(this->client, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchSlot);
}

PlayerStatsWindow::~PlayerStatsWindow()
{
    delete ui;
}

void PlayerStatsWindow::fetchSlot()
{
    lastResponse = client->getLastResponse();
    player->updateAccInfo(lastResponse);
    player->print();
}
