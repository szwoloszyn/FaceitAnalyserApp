#include "matchdatapanel.h"
#include "ui_matchdatapanel.h"

MatchDataPanel::MatchDataPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchDataPanel)
{
    ui->setupUi(this);
}

MatchDataPanel::~MatchDataPanel()
{
    delete ui;
}

void MatchDataPanel::setData(const MatchStats &match)
{
    ui->hltvValue->setText("   " + QString::number(match.hltv, 'f', 2));

    QString kad = QString::number(match.kills) + "/" +
                  QString::number(match.assists) + "/" +
                  QString::number(match.deaths);
    ui->kadValue->setText("   " + kad);

    setUpScore(match);

    setUpMapPicture(match);
}

void MatchDataPanel::setUpScore(const MatchStats& match)
{
    QString score = match.score;
    score.remove(" ");
    QStringList scores = score.split(u'/');
    if (scores.size() != 2) {
        qDebug() << QString(R"(ERROR, %1 scores instead of 2)").arg(scores.size());
        ui->scoreValue->setText("N/A");
        return;
    }
    int score_a = scores.at(0).toInt();
    int score_b = scores.at(1).toInt();
    QString scoreLabel;
    if (match.isWon) {
        scoreLabel = QString::number(qMax(score_a, score_b)) +
                             " / " + QString::number(qMin(score_a, score_b));
    }
    else {
        scoreLabel = QString::number(qMin(score_a, score_b)) +
                             " / " + QString::number(qMax(score_a, score_b));
    }
    ui->scoreValue->setText("   " + scoreLabel);
}

void MatchDataPanel::setUpMapPicture(const MatchStats &match)
{
    if (match.mapPic == "N/A") {
        ui->mapValue->setText(match.mapName);
        return;
    }
    QUrl imageUrl(match.mapPic);
    QNetworkRequest request(imageUrl);
    manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            ui->mapValue->setPixmap(pixmap);
            return;
        }
        qWarning() << "TF HAPPENED";
        reply->deleteLater();
    });

}
