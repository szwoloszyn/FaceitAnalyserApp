#include "playerinputpanel.h"
#include "ui_playerinputpanel.h"

PlayerInputPanel::PlayerInputPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerInputPanel)
{
    ui->setupUi(this);
    connect (ui->confirm, &QPushButton::clicked, this, &PlayerInputPanel::confirm);
}

PlayerInputPanel::~PlayerInputPanel()
{
    delete ui;
}

QString PlayerInputPanel::text() const
{
    return ui->nickname->displayText();
}

void PlayerInputPanel::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->confirm->click();
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

void PlayerInputPanel::confirm()
{
    emit confirmed();
}
