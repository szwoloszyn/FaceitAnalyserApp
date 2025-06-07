#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

PlayerStatsWindow::PlayerStatsWindow(const QString& apiKey, QWidget *parent)
    : QWidget(parent)
    , clientForAccInfo{new FaceitApiClient{apiKey}}
    , clientForStats{new FaceitApiClient{apiKey}}
    , clientForMatches{new FaceitApiClient{apiKey}}
    , player{new Player}
    , accInfoResponse{QJsonObject()}
    , statsResponse{QJsonObject()}
    , matchesResponses{QList<QJsonObject>{}}
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

    // player data assigned -> request stats
    connect(this, &PlayerStatsWindow::accInfoReady,
            this, &PlayerStatsWindow::requestStats);
    // request done -> assign stats data to my object
    connect(this->clientForStats, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchStats);

    // stats assigned -> request matches
    connect(this, &PlayerStatsWindow::statsReady,
            this, &PlayerStatsWindow::requestMatches);
    // request done -> assign matches to my object
    connect(this->clientForMatches, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchMatches);
    // matches assigned -> time to print data onto my screen
    connect(this, &PlayerStatsWindow::matchesReady,
            this, &PlayerStatsWindow::updateView);

    // apiError -> print information
    connect(this->clientForAccInfo, &FaceitApiClient::apiError,
            this, &PlayerStatsWindow::apiErrorCought);
    connect(this->clientForStats, &FaceitApiClient::apiError,
            this, &PlayerStatsWindow::apiErrorCought);
    connect(this->clientForMatches, &FaceitApiClient::apiError,
            this, &PlayerStatsWindow::apiErrorCought);
}

PlayerStatsWindow::~PlayerStatsWindow()
{
    delete ui;
}

void PlayerStatsWindow::fetchAccInfo()
{
    //qDebug() << accInfoResponse;
    accInfoResponse = clientForAccInfo->getLastResponse();
    player->updateAccInfo(accInfoResponse);

    emit accInfoReady();
}

void PlayerStatsWindow::requestAccInfo()
{
    QString url = "https://open.faceit.com/data/v4/players";
    QString nickname = this->ui->nicknameEdit->toPlainText();
    QMap<QString, QString> parameters {
        {"nickname", nickname}
    };
    clientForAccInfo->fetchData(url, parameters);
}

void PlayerStatsWindow::requestStats()
{
    QString url = "https://open.faceit.com/data/v4/players/" +
            this->player->acc_info.value("player_id") +
            "/games/cs2/stats";
    url = "https://open.faceit.com/data/v4/players/" +
        this->player->acc_info.value("player_id") +
        "/stats/cs2";

    QMap<QString, QString> parameters {
        //{"offset", }
    };
    clientForStats->fetchData(url, parameters);
}

void PlayerStatsWindow::fetchStats()
{
    statsResponse = clientForStats->getLastResponse();
    player->updateStats(statsResponse);

    emit statsReady();
}

void PlayerStatsWindow::requestMatches()
{
    QString url = "https://open.faceit.com/data/v4/players/" +
                  this->player->acc_info.value("player_id") +
                  "/games/cs2/stats";
    int matchesToGo = this->accInfoResponse.value("number_of_cs2_matches").toInt();
    int offset = 0;
    // TODO WHILE LOOP
    while (matchesToGo > 0 or offset >= 200) {
        // int limit = (matchesToGo >= 100) ? 100 : matchesToGo;
        // matchesToGo -= limit;
        // QMap<QString, QString> parameters {
        //     {"limit", QString::number(limit)},
        //     {"offset", QString::number(offset)}
        // };
        // clientForMatches->fetchData(url, parameters);
        // offset += limit;
    }
    int limit = 50;
    QMap<QString, QString> parameters {
        {"limit", QString::number(limit)},
        {"offset", QString::number(offset)}
    };
    clientForMatches->fetchData(url, parameters);


}

void PlayerStatsWindow::fetchMatches()
{
    matchesResponses.append(clientForMatches->getLastResponse());
    //player->updateMatches(matchesResponse);

    emit matchesReady();
}

void PlayerStatsWindow::updateView()
{
    //qDebug() << accInfoResponse;
    player->print();
    if (matchesResponses.isEmpty()) {
        qDebug() << "EMPTY";
    }
    else {
        qDebug() << "ITEMED" << matchesResponses.size();
    }
    //qDebug() << statsResponse;
    for (auto it = player->acc_info.constBegin(); it != player->acc_info.constEnd(); ++it) {
        ui->data->setText(ui->data->text() + "\n" + it.key() + " " + it.value());
    }
}

void PlayerStatsWindow::apiErrorCought()
{
    ui->data->setText("invalid nickname");
}
