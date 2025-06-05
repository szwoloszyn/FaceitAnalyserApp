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
    void readyToView();

private slots:
    void fetchSlot();
    void requestData();
    void updateView();

private:
    FaceitApiClient* client;
    Player* player;
    QJsonObject lastResponse;

    Ui::PlayerStatsWindow *ui;
};
#endif // PLAYERSTATSWINDOW_H
