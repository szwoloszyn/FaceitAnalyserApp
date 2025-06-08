#include "playerstatswindow.h"
#include "./ui_playerstatswindow.h"

constexpr int MAX_TO_FETCH = 300;

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
    // request done -> asking for next batch
    connect(this->clientForMatches, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsWindow::fetchMatchesBatch);
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
    delete clientForAccInfo;
    delete clientForStats;
    delete clientForMatches;
    delete player;
}

void PlayerStatsWindow::fetchAccInfo()
{
    accInfoResponse = clientForAccInfo->getLastResponse();
    player->updateAccInfo(accInfoResponse);

    emit accInfoReady();
}

void PlayerStatsWindow::requestAccInfo()
{
    this->clear();
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
    int maxToFetch = MAX_TO_FETCH;
    int matchesToGo = this->player->acc_info.value("number_of_cs2_matches").toInt();
    if (matchesToGo > maxToFetch) {
        matchesToGo = maxToFetch;
    }

    this->remainingMatches = matchesToGo;
    this->offset = 0;
    requestNextMatchesBatch();
}

void PlayerStatsWindow::requestNextMatchesBatch()
{
    if (remainingMatches <= 0) {
        return;
    }
    QString url = "https://open.faceit.com/data/v4/players/" +
                  this->player->acc_info.value("player_id") +
                  "/games/cs2/stats";
    int limit = qMin(remainingMatches, 100);
    QMap<QString, QString> parameters {
        {"limit", QString::number(limit)},
        {"offset", QString::number(offset)}
    };
    qDebug() << "Sending match stats request: limit=" <<
        parameters.value("limit") <<
        ", offset=" << parameters.value("offset");

    clientForMatches->fetchData(url, parameters);

    this->offset += limit;
    remainingMatches -= limit;
}

void PlayerStatsWindow::fetchMatchesBatch()
{
    matchesResponses.append(clientForMatches->getLastResponse());

    if (remainingMatches > 0 and offset <= 200) {
        QTimer::singleShot(150, this, &PlayerStatsWindow::requestNextMatchesBatch);
    }
    else {
        this->player->updateMatches(matchesResponses);
        this->player->updateLifetimeFromMatches();
        emit matchesReady();
    }
}

void PlayerStatsWindow::updateView()
{
    player->print();

    qDebug() << matchesResponses.size();
    // GUI
    for (auto it = player->acc_info.constBegin(); it != player->acc_info.constEnd(); ++it) {
        ui->data->setText(ui->data->text() + "\n" + it.key() + " " + it.value());
    }
}

void PlayerStatsWindow::apiErrorCought()
{
    // GUI
    ui->data->setText("invalid nickname");
}

void PlayerStatsWindow::clear()
{
    accInfoResponse = QJsonObject();
    statsResponse = QJsonObject();
    matchesResponses = QList<QJsonObject>();
    delete player;
    player = new Player();

    // GUI
    ui->data->setText("");
}


