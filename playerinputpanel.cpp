#include "playerinputpanel.h"
#include "ui_playerinputpanel.h"

PlayerInputPanel::PlayerInputPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerInputPanel)
{
    ui->setupUi(this);
    connect (ui->confirm, &QPushButton::clicked, this, &PlayerInputPanel::confirm);
    // TO BE CHANGED BACK
    //connect (ui->last50Box, &QCheckBox::checkStateChanged, this, &PlayerInputPanel::confirm);
    connect (ui->last50Box, &QCheckBox::stateChanged, this, &PlayerInputPanel::confirm);
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
    bool isLast50 = false;
    if (ui->last50Box->checkState() == Qt::Checked) {
        isLast50 = true;
    }
    QString nickname = ui->nickname->displayText();
    emit confirmed(nickname, isLast50);
}
