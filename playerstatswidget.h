#ifndef PLAYERSTATSWIDGET_H
#define PLAYERSTATSWIDGET_H

#include <QWidget>
#include "playerdatapanel.h"
#include "playerinputpanel.h"
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

    void setInvalidNickname();
signals:
    void dataRequested(QString nickname, bool isLast50);

private slots:
    void requestData(QString nickname, bool isLast50);
private:
    Ui::PlayerStatsWidget *ui;
};

#endif // PLAYERSTATSWIDGET_H
