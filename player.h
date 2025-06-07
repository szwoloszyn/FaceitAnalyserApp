#ifndef PLAYER_H
#define PLAYER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMap>
#include <QList>

struct PlayerStats
{
    QString hs_rate = "x";
    QString adr= "x";
    QString kdr= "x";
    QString hltv= "x";
};

struct MatchStats
{
    double adr = 0;
    double kdr = 0;
    double kpr = 0;
    int kills = 0;
    int assists = 0;
    int deaths = 0;

    int double_kills = 0;
    int triple_kills = 0;
    int quad_kills = 0;
    int aces = 0;
    int rounds = 0;

    double hltv = 0;
};

double calculateHltv(const MatchStats& stats);

class Player
{
public:
    Player();
    void updateAccInfo(const QJsonObject& acc);
    void updateStats(const QJsonObject& stats);
    void updateMatches(const QList<QJsonObject>& matches);

    void print();
public:
    QMap <QString, QString> acc_info; // <variable name, value>
    PlayerStats lifetime_stats;
    QMap <QString,PlayerStats> match_stats; // <match_id, stats>
};

#endif // PLAYER_H
