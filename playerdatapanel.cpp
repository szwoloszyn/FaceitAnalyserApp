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

    QString matchesLabel = QString(R"(%1 played %2 matches on Faceit)").arg(player->acc_info.value("nickname"), player->acc_info.value("number_of_matches"));
    ui->matchesNum->setText(matchesLabel);

    int elo = player->acc_info.value("elo").toInt();
    setUpProgressBar(elo);
    setUpProfilePicture(player->acc_info.value("avatar"));

    int level = player->acc_info.value("level").toInt();
    setUpLevelPicture(level);
}

void PlayerDataPanel::setUpProgressBar(int elo)
{
    if (elo > 2001) {
        elo = 2001;
    }
    ui->lvlProgress->setValue(elo);
    // TODO this aint working
    QPixmap pixmap(":/background_imgs/resources/elobar.png");
    QString style = QString(R"(
        QProgressBar {
            border: 2px solid gray;
            border-radius: 5px;
            background-image: url(:/background_imgs/resources/elobar_scaled.png) 0 0 0 0 stretch stretch;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: transparent;
            width: 10px;
            margin: 0px;
        }
    )");
    ui->lvlProgress->setStyleSheet(style);
}

void PlayerDataPanel::setUpProfilePicture(const QString& picture)
{
    if (picture != "") {
        QUrl imageUrl(picture);
        QNetworkRequest request(imageUrl);
        manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray imageData = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(imageData);
                ui->profilePic->setPixmap(pixmap);
                return;
            }
            reply->deleteLater();
        });
    }
    else {
        QPixmap pixmap(":/profile_pic/resources/def_avatar.jpg");
        ui->lvlPic->setScaledContents(true);
        ui->profilePic->setPixmap(pixmap);
        return;
    }
}

void PlayerDataPanel::setUpLevelPicture(int level)
{
    QString lvlImg = QString(R"(:/lvl/resources/lvls/%1.png)").arg(level);
    QPixmap pixmap(lvlImg);
    QPixmap scaled = pixmap.scaled(ui->lvlPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //ui->lvlPic->setScaledContents(true);
    ui->lvlPic->setPixmap(scaled);
}
