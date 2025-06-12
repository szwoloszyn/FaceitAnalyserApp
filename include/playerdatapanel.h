#ifndef PLAYERDATAPANEL_H
#define PLAYERDATAPANEL_H

#include <QWidget>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

#include "player.h"

namespace Ui {
class PlayerDataPanel;
}

class PlayerDataPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerDataPanel(QWidget *parent = nullptr);
    ~PlayerDataPanel();
    void setData(const Player* player);

private:
    void setUpProgressBar(int elo);
    void setUpProfilePicture(const QString& picture);
    void setUpLevelPicture(int level);
    QNetworkAccessManager* manager;
    Ui::PlayerDataPanel *ui;

private:
    PlayerDataPanel(const PlayerDataPanel&) = delete;
    PlayerDataPanel& operator=(const PlayerDataPanel&) = delete;
};

#endif // PLAYERDATAPANEL_H
