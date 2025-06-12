#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "playerstatsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& apiKey, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void requestPlayer(const QString& nickname, bool isLast50);
    void requestMatch(const QString& match_id);
    void update();
    void updateInvalid(const QString& error);

    void pageToPlayer();
    void pageToMatch();
private:
    Ui::MainWindow *ui;
    PlayerStatsManager* manager;

private:
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
};

#endif // MAINWINDOW_H
