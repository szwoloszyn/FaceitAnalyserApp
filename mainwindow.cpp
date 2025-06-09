#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString& apiKey, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new PlayerStatsManager{apiKey, this})
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->playerStats);
    connect (ui->playerStats, &PlayerStatsWidget::dataRequested, this, &MainWindow::request);
    connect (this->manager, &PlayerStatsManager::allReady, this, &MainWindow::update);
    connect (this->manager, &PlayerStatsManager::invalidNicknameGiven, this, &MainWindow::updateInvalid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::request(QString nickname, bool isLast50)
{
    manager->changeLast50State(isLast50);
    manager->startRequest(nickname);
}

void MainWindow::update()
{
    ui->playerStats->setData(manager->getPlayer());
}

void MainWindow::updateInvalid()
{
    ui->playerStats->setInvalidNickname();
}
