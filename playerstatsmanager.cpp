#include "playerstatsmanager.h"


constexpr int MAX_TO_FETCH = 300;

PlayerStatsManager::PlayerStatsManager(const QString& apiKey, QObject *parent)
    : QObject(parent)
    , clientForAccInfo{new FaceitApiClient{apiKey}}
    , clientForStats{new FaceitApiClient{apiKey}}
    , clientForMatches{new FaceitApiClient{apiKey}}
    , player{new Player}
    , accInfoResponse{QJsonObject()}
    , statsResponse{QJsonObject()}
    , matchesResponses{QList<QJsonObject>{}}
{
    // clicked -> request acc info
    connect(this, &PlayerStatsManager::requestStarted,
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
    // matches assigned -> signal window that data is ready
    connect(this, &PlayerStatsManager::matchesReady,
            this, &PlayerStatsManager::reportReadiness);

    // apiError -> signal of the error further
    connect(this->clientForAccInfo, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
    connect(this->clientForStats, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
    connect(this->clientForMatches, &FaceitApiClient::apiError,
            this, &PlayerStatsManager::apiErrorCought);
}

PlayerStatsManager::~PlayerStatsManager()
{
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

void PlayerStatsManager::requestAccInfo(const QString& nickname)
{
    this->clear();
    QString url = "https://open.faceit.com/data/v4/players";
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
    int limit = 100;
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

void PlayerStatsManager::reportReadiness()
{
    player->print();
    emit allReady();

    qDebug() << "FINISHED";
}

void PlayerStatsManager::apiErrorCought(const QString& error)
{
    emit invalidRequest(error);
}

void PlayerStatsManager::changeLast50State(bool isLast50)
{
    last50matches = isLast50;
}

void PlayerStatsManager::startRequest(const QString& nickname)
{
    emit requestStarted(nickname);
}

Player* PlayerStatsManager::getPlayer() const
{
    return player;
}

void PlayerStatsManager::clear()
{
    accInfoResponse = QJsonObject();
    statsResponse = QJsonObject();
    matchesResponses = QList<QJsonObject>();
    delete player;
    player = new Player();
}


