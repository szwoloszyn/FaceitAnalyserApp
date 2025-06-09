#include "playerstatsmanager.h"
#include "./ui_playerstatsmanager.h"

constexpr int MAX_TO_FETCH = 300;

PlayerStatsManager::PlayerStatsManager(const QString& apiKey, QWidget *parent)
    : QWidget(parent)
    , clientForAccInfo{new FaceitApiClient{apiKey}}
    , clientForStats{new FaceitApiClient{apiKey}}
    , clientForMatches{new FaceitApiClient{apiKey}}
    , player{new Player}
    , accInfoResponse{QJsonObject()}
    , statsResponse{QJsonObject()}
    , matchesResponses{QList<QJsonObject>{}}
    , ui(new Ui::PlayerStatsManager)
{
    this->setMinimumSize(400, 300);
    ui->setupUi(this);
    // clicked -> request acc
    connect(this->ui->confirm, &QPushButton::clicked,
            this, &PlayerStatsManager::requestAccInfo);
    // request done -> assign player data to my object
    connect(this->clientForAccInfo, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsManager::fetchAccInfo);

    // player data assigned -> request stats
    connect(this, &PlayerStatsManager::accInfoReady,
            this, &PlayerStatsManager::requestStats);
    // request done -> assign stats data to my object
    connect(this->clientForStats, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsManager::fetchStats);

    // stats assigned -> request matches
    connect(this, &PlayerStatsManager::statsReady,
            this, &PlayerStatsManager::requestMatches);
    // request done -> asking for next batch
    connect(this->clientForMatches, &FaceitApiClient::playerDataReady,
            this, &PlayerStatsManager::fetchMatchesBatch);
    // matches assigned -> time to print data onto my screen
    connect(this, &PlayerStatsManager::matchesReady,
            this, &PlayerStatsManager::updateView);

    // apiError -> print information
    connect(this->clientForAccInfo, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
    connect(this->clientForStats, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
    connect(this->clientForMatches, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
}

PlayerStatsManager::~PlayerStatsManager()
{
    delete ui;
    delete clientForAccInfo;
    delete clientForStats;
    delete clientForMatches;
    delete player;
}

void PlayerStatsManager::fetchAccInfo()
{
    accInfoResponse = clientForAccInfo->getLastResponse();
    player->updateAccInfo(accInfoResponse);

    emit accInfoReady();
}

void PlayerStatsManager::requestAccInfo()
{
    this->clear();
    QString url = "https://open.faceit.com/data/v4/players";
    QString nickname = this->ui->nicknameEdit->toPlainText();
    QMap<QString, QString> parameters {
        {"nickname", nickname}
    };
    clientForAccInfo->fetchData(url, parameters);
}

void PlayerStatsManager::requestStats()
{
    QString url = "https://open.faceit.com/data/v4/players/" +
                  this->player->acc_info.value("player_id") +
                  "/games/cs2/stats";
    url = "https://open.faceit.com/data/v4/players/" +
          this->player->acc_info.value("player_id") +
          "/stats/cs2";

    QMap<QString, QString> parameters {

    };
    clientForStats->fetchData(url, parameters);
}

void PlayerStatsManager::fetchStats()
{
    statsResponse = clientForStats->getLastResponse();
    player->updateStats(statsResponse);

    emit statsReady();
}

void PlayerStatsManager::requestMatches()
{
    QString url = "https://open.faceit.com/data/v4/players/" +
                  this->player->acc_info.value("player_id") +
                  "/games/cs2/stats";
    int maxToFetch = MAX_TO_FETCH;
    int matchesToGo = 0;
    if (last50matches) {
        matchesToGo = qMin(this->player->acc_info.value("number_of_cs2_matches").toInt(), 50);
    }
    else {
        matchesToGo = this->player->acc_info.value("number_of_cs2_matches").toInt();
    }
    if (matchesToGo > maxToFetch) {
        matchesToGo = maxToFetch;
    }

    this->remainingMatches = matchesToGo;
    this->offset = 0;
    requestNextMatchesBatch();
}

void PlayerStatsManager::requestNextMatchesBatch()
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
    // DEBUG PRINTS
    qDebug() << "Sending match stats request: limit=" <<
        parameters.value("limit") <<
        ", offset=" << parameters.value("offset");
    qDebug() << url;
    clientForMatches->fetchData(url, parameters);

    this->offset += limit;
    remainingMatches -= limit;
}

void PlayerStatsManager::fetchMatchesBatch()
{
    matchesResponses.append(clientForMatches->getLastResponse());

    if (remainingMatches > 0 and offset <= 200) {
        QTimer::singleShot(150, this, &PlayerStatsManager::requestNextMatchesBatch);
    }
    else {
        this->player->updateMatches(matchesResponses);
        this->player->updateLifetimeFromMatches();
        emit matchesReady();
    }
}

void PlayerStatsManager::updateView()
{
    player->print();
    // GUI
    for (auto it = player->acc_info.constBegin(); it != player->acc_info.constEnd(); ++it) {
        ui->data->setText(ui->data->text() + "\n" + it.key() + " " + it.value());
    }
    qDebug() << "FINISHED";
}

void PlayerStatsManager::apiErrorCought()
{
    // GUI
    ui->data->setText("invalid nickname");
}

void PlayerStatsManager::changeLast50State()
{
    last50matches = !last50matches;
}

void PlayerStatsManager::clear()
{
    accInfoResponse = QJsonObject();
    statsResponse = QJsonObject();
    matchesResponses = QList<QJsonObject>();
    delete player;
    player = new Player();

    // GUI
    ui->data->setText("");
}


