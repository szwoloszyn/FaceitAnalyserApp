#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

PlayerStatsWindow::PlayerStatsWindow(const QString& apiKey, QWidget *parent)
    : QWidget(parent)
    , clientForAccInfo{new FaceitApiClient{apiKey}}
    , clientForMatches{new FaceitApiClient{apiKey}}
    , player{new Player}
    , accInfoResponse{QJsonObject()}
    , matchesResponse{QJsonObject()}
    , ui(new Ui::PlayerStatsWindow)
{
    this->setMinimumSize(400, 300);
    ui->setupUi(this);
    // clicked -> request acc
    connect(this->ui->confirm, &QPushButton::clicked,
            this, &PlayerStatsWindow::requestAccInfo);
    // request done -> assign player data to my object
    connect(this->clientForAccInfo, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchAccInfo);

    // player data assigned -> request matches
    connect(this, &PlayerStatsWindow::accInfoReady,
            this, &PlayerStatsWindow::requestMatches);
    // request done -> assign matches data to my object
    connect(this->clientForMatches, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchMatches);
    // matches assigned -> time to print data onto my screen
    connect(this, &PlayerStatsWindow::matchesReady,
            this, &PlayerStatsWindow::updateView);
}

PlayerStatsWindow::~PlayerStatsWindow()
{
    delete ui;
}

void PlayerStatsWindow::fetchAccInfo()
{
    qDebug() << accInfoResponse;
    accInfoResponse = clientForAccInfo->getLastResponse();
    player->updateAccInfo(accInfoResponse);
    player->print();
    emit accInfoReady();
}

void PlayerStatsWindow::requestAccInfo()
{
    QString url = "https://open.faceit.com/data/v4/players?nickname=";
    QString nickname = this->ui->nicknameEdit->toPlainText();
    clientForAccInfo->fetchData(url, nickname);
    QString player_id = player->acc_info.value("player_id");

}

void PlayerStatsWindow::requestMatches()
{
    QString url = "https://open.faceit.com/data/v4/players/" +
            this->player->acc_info.value("player_id") +
            "/games/cs2/stats";
    // BUG INIFNITE LOOP OF REQUESTS !
    clientForMatches->fetchData(url);
}

void PlayerStatsWindow::updateView()
{
    for (auto it = player->acc_info.constBegin(); it != player->acc_info.constEnd(); ++it) {
        ui->data->setText(ui->data->text() + "\n" + it.key() + " " + it.value());
    }
}
