#ifndef PLAYERSTATSWINDOW_H
#define PLAYERSTATSWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerStatsWindow; }
QT_END_NAMESPACE

class PlayerStatsWindow : public QWidget
{
    Q_OBJECT

public:
    PlayerStatsWindow(QWidget *parent = nullptr);
    ~PlayerStatsWindow();

private:
    Ui::PlayerStatsWindow *ui;
};
#endif // PLAYERSTATSWINDOW_H
