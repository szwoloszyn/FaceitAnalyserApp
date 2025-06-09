#ifndef PLAYERSTATSMANAGER_H
#define PLAYERSTATSMANAGER_H

#include <QWidget>
#include <QList>
#include <QTimer>

#include "player.h"
#include "faceitapiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerStatsManager; }
QT_END_NAMESPACE

class PlayerStatsManager : public QWidget
{
    Q_OBJECT

public:
    PlayerStatsManager(const QString& apiKey, QWidget *parent = nullptr);
    ~PlayerStatsManager();

    void changeLast50State(bool isLast50);
    void startRequest();
    Player* getPlayer() const;

signals:
    void requestStarted();
    void accInfoReady();
    void statsReady();
    void matchesReady();
    void allReady();

    void invalidNicknameGiven();

private slots:
    void fetchAccInfo();
    void requestAccInfo();

    void requestStats();
    void fetchStats();

    void requestMatches();
    void fetchMatchesBatch();

    // WARNING debug-only implementation
    void updateView();

    void apiErrorCought();



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

    Ui::PlayerStatsManager *ui;
};
#endif // PLAYERSTATSMANAGER_H
