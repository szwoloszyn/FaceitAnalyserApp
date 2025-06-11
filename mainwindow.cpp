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
    connect (this->manager, &PlayerStatsManager::invalidRequest, this, &MainWindow::updateInvalid);

    connect(this->ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(this->ui->actionPlayer_stats, &QAction::triggered, this, &MainWindow::pageToPlayer);
    connect(this->ui->actionMatch_stats, &QAction::triggered, this, &MainWindow::pageToMatch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::request(const QString& nickname, bool isLast50)
{
    manager->changeLast50State(isLast50);
    manager->startRequest(nickname);
}

void MainWindow::update()
{
    ui->playerStats->setData(manager->getPlayer());
}

void MainWindow::updateInvalid(const QString& error)
{
    ui->playerStats->setErrorOnCall(error);
}

void MainWindow::pageToPlayer()
{
    ui->stackedWidget->setCurrentWidget(ui->playerStats);
}

void MainWindow::pageToMatch()
{
    ui->stackedWidget->setCurrentWidget(ui->matchStats);
}
