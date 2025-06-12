#include "playerdatapanel.h"
#include "./ui_playerdatapanel.h"

QString calculateColorForLevel(int elo);
double calculateCurrentLevelProgress(int elo);

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
    ui->lvlProgress->setRange(0,100);
    ui->lvlProgress->setValue(static_cast<int>(100*calculateCurrentLevelProgress(elo)));
    QString color = calculateColorForLevel(elo);
    QPixmap pixmap(":/background_imgs/resources/elobar.png");
    QString style = QString(R"(
        QProgressBar {
            border: 2px solid gray;
            border-radius: 5px;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: %1;
            width: 10px;
        }
    )").arg(color);
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
    QPixmap pixmap(":/profile_pic/resources/def_avatar.jpg");
    ui->lvlPic->setScaledContents(true);
    ui->profilePic->setPixmap(pixmap);
    return;
}

void PlayerDataPanel::setUpLevelPicture(int level)
{
    QString lvlImg = QString(R"(:/lvl/resources/lvls/%1.png)").arg(level);
    QPixmap pixmap(lvlImg);
    QPixmap scaled = pixmap.scaled(ui->lvlPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->lvlPic->setPixmap(scaled);
}

QString calculateColorForLevel(int elo)
{
    if (elo < 501) {
       return "#eeeeee"; // gray
    }
    if (elo < 901) {
        return "#19ca00"; // green
    }
    if (elo < 1531) {
        return "#ffc800"; // yellow
    }
    if (elo < 2001) {
        return "#ff6309"; // orange
    }
    return "#fe1f00"; // red
}

double calculateCurrentLevelProgress(int elo)
{
    if (elo >= 2001) {
        return 1.0;
    }
    struct LevelRange {
        int level;
        int eloMin;
        int eloMax;
    };

    std::vector<LevelRange> levels = {
        {1, 100, 500},
        {2, 501, 750},
        {3, 751, 900},
        {4, 901, 1050},
        {5, 1051, 1200},
        {6, 1201, 1350},
        {7, 1351, 1530},
        {8, 1531, 1750},
        {9, 1751, 2000},
    };

    for (const auto& level : levels) {
        if (elo >= level.eloMin && elo <= level.eloMax) {
            double progress = static_cast<double>(elo - level.eloMin) / (level.eloMax - level.eloMin);
            return progress;
        }
    }

    return 0.0;
}
