#include "matchinputpanel.h"
#include "ui_matchinputpanel.h"

MatchInputPanel::MatchInputPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchInputPanel)
{
    ui->setupUi(this);
    ui->matchID->setPlaceholderText("insert nickname here");
    ui->matchID->setText("");
}

MatchInputPanel::~MatchInputPanel()
{
    delete ui;
}

QString MatchInputPanel::text() const
{
    QString match_id = ui->matchID->text();
    // TODO parse id out of link
    return match_id;
}
