#ifndef PLAYERDATAPANEL_H
#define PLAYERDATAPANEL_H

#include <QWidget>

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
    Ui::PlayerDataPanel *ui;
};

#endif // PLAYERDATAPANEL_H
