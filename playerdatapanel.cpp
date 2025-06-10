#include "playerdatapanel.h"
#include "./ui_playerdatapanel.h"

PlayerDataPanel::PlayerDataPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerDataPanel)
{
    ui->setupUi(this);
    ui->lvlProgress->setRange(100,2001);
}

PlayerDataPanel::~PlayerDataPanel()
{
    delete ui;
}

void PlayerDataPanel::setData(const Player *player)
{
    ui->ADR->setText(player->lifetime_stats.adr);
    ui->KDR->setText(player->lifetime_stats.kdr);
    ui->HLTV->setText(player->lifetime_stats.hltv);
    ui->elo->setText(player->acc_info.value("elo") + " ELO");

    int elo = player->acc_info.value("elo").toInt();
    setUpProgressBar(elo);
    setUpProfilePicture(player->acc_info.value("avatar"));

}

void PlayerDataPanel::setUpProgressBar(int elo)
{
    if (elo > 2001) {
        elo = 2001;
    }
    ui->lvlProgress->setValue(elo);
}

void PlayerDataPanel::setUpProfilePicture(const QString& picture)
{
    qDebug() << "AV: " << picture;
    if (picture != "") {
        qDebug() << "AV: " << picture;
        QUrl imageUrl(picture);
        QNetworkRequest request(imageUrl);
        manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            qDebug() << "AV: " << picture;
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray imageData = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(imageData);
                qDebug() << "EMMM HELLO?";
                ui->profilePic->setPixmap(pixmap);
                return;
            }
            else {
                qDebug() << "SHOULDNT BE HERE";
            }
            reply->deleteLater();
        });
    }
    else {
        QPixmap pixmap(":/profile_pic/resources/def_avatar.jpg");
        QPixmap newpixmap(":/lvl/resources/lvls/10.png");
        qDebug() << "%%%" << pixmap.isNull();
        ui->profilePic->setPixmap(pixmap);
        return;
    }

}
