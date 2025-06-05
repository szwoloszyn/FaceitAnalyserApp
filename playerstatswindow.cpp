#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

PlayerStatsWindow::PlayerStatsWindow(const QString& apiKey, QWidget *parent)
    : QWidget(parent)
    , client{new FaceitApiClient{apiKey}}
    , player{new Player}
    , lastResponse{QJsonObject()}
    , ui(new Ui::PlayerStatsWindow)
{
    this->setMinimumSize(400, 300);
    ui->setupUi(this);
    connect(this->client, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchSlot);
    connect(this->ui->confirm, &QPushButton::clicked, this, &PlayerStatsWindow::requestData);
    connect(this, &PlayerStatsWindow::readyToView, this, &PlayerStatsWindow::updateView);
}

PlayerStatsWindow::~PlayerStatsWindow()
{
    delete ui;
}

void PlayerStatsWindow::fetchSlot()
{
    qDebug() << lastResponse;
    lastResponse = client->getLastResponse();
    player->updateAccInfo(lastResponse);
    emit readyToView();
}

void PlayerStatsWindow::requestData()
{
    QString url = "https://open.faceit.com/data/v4/players?nickname=";
    QString nickname = this->ui->nicknameEdit->toPlainText();
    client->fetchData(url, nickname);
    QString player_id = player->acc_info.value("player_id");
    url = ("https://open.faceit.com/data/v4/players/ad5adc8e-f25f-44d5-8719-af15ff232982/games/cs2/stats");
    client->fetchData(url);
}

void PlayerStatsWindow::updateView()
{
    for (auto it = player->acc_info.constBegin(); it != player->acc_info.constEnd(); ++it) {
        ui->data->setText(ui->data->text() + "\n" + it.key() + " " + it.value());
    }
}
