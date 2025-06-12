#ifndef MATCHDATAPANEL_H
#define MATCHDATAPANEL_H

#include <QWidget>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>
#include <QStringList>

#include "player.h"

namespace Ui {
class MatchDataPanel;
}

class MatchDataPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MatchDataPanel(QWidget *parent = nullptr);
    ~MatchDataPanel();
    void setData(const MatchStats& match);
    void setUpScore(const MatchStats& match);
    void setUpMapPicture(const MatchStats& match);

private:
    Ui::MatchDataPanel *ui;
    QNetworkAccessManager* manager;

private:
    MatchDataPanel(const MatchDataPanel&) = delete;
    MatchDataPanel& operator=(const MatchDataPanel&) = delete;
};

#endif // MATCHDATAPANEL_H
