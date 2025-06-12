#ifndef PLAYERSTATSWIDGET_H
#define PLAYERSTATSWIDGET_H

#include <QWidget>

#include "player.h"

namespace Ui {
class PlayerStatsWidget;
}

class PlayerStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerStatsWidget(QWidget *parent = nullptr);
    ~PlayerStatsWidget();
    void setData(const Player* player);

    void setErrorOnCall(const QString& error);

    bool isAllValid() const;
signals:
    void dataRequested(const QString& nickname, bool isLast50);

private slots:
    void requestData(const QString& nickname, bool isLast50);
private:
    Ui::PlayerStatsWidget *ui;

private:
    PlayerStatsWidget(const PlayerStatsWidget&) = delete;
    PlayerStatsWidget& operator=(const PlayerStatsWidget&) = delete;
};

#endif // PLAYERSTATSWIDGET_H
