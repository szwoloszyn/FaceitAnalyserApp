#ifndef PLAYER_H
#define PLAYER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMap>


// TODO do it as a map ?
struct PlayerStats
{
    QString kills;
    QString assists;
    QString deaths;
    QString hs_rate;
    QString kpd;
    QString kpr;
};

struct MatchStats
{

};

class Player
{
public:
    Player();
    void updateAccInfo(const QJsonObject& acc);
    void print();
public:
    QMap <QString, QString> acc_info; // <variable name, value>
    PlayerStats lifetime_stats;
    QMap <QString,PlayerStats> match_stats; // <match_id, stats>
};

#endif // PLAYER_H
