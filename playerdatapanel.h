#ifndef PLAYERDATAPANEL_H
#define PLAYERDATAPANEL_H

#include <QWidget>

namespace Ui {
class PlayerDataPanel;
}

class PlayerDataPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerDataPanel(QWidget *parent = nullptr);
    ~PlayerDataPanel();

private:
    Ui::PlayerDataPanel *ui;
};

#endif // PLAYERDATAPANEL_H
