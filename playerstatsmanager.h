#ifndef PLAYERSTATSMANAGER_H
#define PLAYERSTATSMANAGER_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QTimer>

#include "player.h"
#include "faceitapiclient.h"


class PlayerStatsManager : public QObject
{
    Q_OBJECT

public:
    PlayerStatsManager(const QString& apiKey, QObject *parent = nullptr);
    ~PlayerStatsManager();

    void changeLast50State(bool isLast50);
    void startRequest(const QString& nickname);
    Player* getPlayer() const;

signals:
    void requestStarted(const QString& nickname);
    void accInfoReady();
    void statsReady();
    void matchesReady();
    void allReady();

    void invalidRequest(const QString& error);

private slots:
    void fetchAccInfo();
    void requestAccInfo(const QString& nickname);

    void requestStats();
    void fetchStats();

    void requestMatches();
    void fetchMatchesBatch();

    void reportReadiness();

    void apiErrorCought(const QString& error);



private:
    void clear();

    bool last50matches = true;
    void requestNextMatchesBatch();
    int remainingMatches = 0;
    int offset = 0;


    FaceitApiClient* clientForAccInfo;
    FaceitApiClient* clientForStats;
    FaceitApiClient* clientForMatches;
    QJsonObject accInfoResponse;
    QJsonObject statsResponse;
    QList<QJsonObject> matchesResponses;
    Player* player;
};
#endif // PLAYERSTATSMANAGER_H
