#ifndef PLAYERSTATSWINDOW_H
#define PLAYERSTATSWINDOW_H

#include <QWidget>
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

    void matchesReady();

private slots:
    void fetchAccInfo();
    void requestAccInfo();

    // TODO IMPLEMENT
    void requestMatches();
    void fetchMatches();

    // WARNING old version
    void updateView();

private:
    FaceitApiClient* clientForAccInfo;
    FaceitApiClient* clientForMatches;
    QJsonObject accInfoResponse;
    QJsonObject matchesResponse;
    Player* player;

    Ui::PlayerStatsWindow *ui;
};
#endif // PLAYERSTATSWINDOW_H
