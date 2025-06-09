#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void request(QString nickname, bool isLast50);
    void update();
    void updateInvalid();
private:
    Ui::MainWindow *ui;
    PlayerStatsManager* manager;
};

#endif // MAINWINDOW_H
