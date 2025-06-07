#ifndef PLAYERSTATSWINDOW_H
#define PLAYERSTATSWINDOW_H

#include <QWidget>
#include <QList>
#include <QTimer>

#include "player.h"
#include "faceitapiclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerStatsWindow; }
QT_END_NAMESPACE

class PlayerStatsWindow : public QWidget
{
    Q_OBJECT

public:
    PlayerStatsWindow(const QString& apiKey, QWidget *parent = nullptr);
    ~PlayerStatsWindow();

signals:
    void accInfoReady();

    void statsReady();

    void matchesReady();

private slots:
    void fetchAccInfo();
    void requestAccInfo();

    void requestStats();
    void fetchStats();

    void requestMatches();
    void fetchMatchesBatch();

    // WARNING old version
    void updateView();

    void apiErrorCought();

private:
    void clear();

    void requestNextMatchesBatch();
    int remainingMatches = 0;
    int offset = 0;;

    FaceitApiClient* clientForAccInfo;
    FaceitApiClient* clientForStats;
    FaceitApiClient* clientForMatches;
    QJsonObject accInfoResponse;
    QJsonObject statsResponse;
    QList<QJsonObject> matchesResponses;
    //QJsonObject matchesResponse;
    Player* player;

    Ui::PlayerStatsWindow *ui;
};
#endif // PLAYERSTATSWINDOW_H
