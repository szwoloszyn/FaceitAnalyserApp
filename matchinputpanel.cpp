#include "matchinputpanel.h"
#include "ui_matchinputpanel.h"

MatchInputPanel::MatchInputPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchInputPanel)
{
    ui->setupUi(this);
    ui->matchID->setPlaceholderText("insert match id or matchroom link here");
    ui->matchID->setText("");

    connect(ui->confirm, &QPushButton::clicked, this, &MatchInputPanel::confirm);
}

MatchInputPanel::~MatchInputPanel()
{
    delete ui;
}

QString MatchInputPanel::text() const
{
    QString match_id = ui->matchID->text();
    if (!match_id.contains("/")) {
        return match_id;
    }
    auto lastSlash = match_id.lastIndexOf("/");
    match_id.remove(0,lastSlash+1);
    return match_id;
}

void MatchInputPanel::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->confirm->click();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

void MatchInputPanel::confirm()
{
    qDebug() << this->text();
    emit confirmed(this->text());
}
