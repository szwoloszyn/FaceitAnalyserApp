#ifndef PLAYERSTATSWIDGET_H
#define PLAYERSTATSWIDGET_H

#include <QWidget>
#include "playerdatapanel.h"
#include "playerinputpanel.h"
namespace Ui {
class PlayerStatsWidget;
}

class PlayerStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerStatsWidget(QWidget *parent = nullptr);
    ~PlayerStatsWidget();

private:
    Ui::PlayerStatsWidget *ui;
};

#endif // PLAYERSTATSWIDGET_H
