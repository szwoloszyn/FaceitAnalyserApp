#ifndef PLAYER_H
#define PLAYER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMap>


struct PlayerStats
{

    QString kills = "x";
    QString assists = "x";
    QString deaths = "x";
    QString hs_rate = "x";
    QString adr= "x";
    QString kdr= "x";
    QString hltv= "x";
};

struct MatchStats
{

};

class Player
{
public:
    Player();
    void updateAccInfo(const QJsonObject& acc);
    void updateStats(const QJsonObject& stats);
    void updateMatches(const QJsonObject& matches);

    void print();
public:
    QMap <QString, QString> acc_info; // <variable name, value>
    PlayerStats lifetime_stats;
    QMap <QString,PlayerStats> match_stats; // <match_id, stats>
};

#endif // PLAYER_H
