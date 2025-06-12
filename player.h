#ifndef PLAYER_H
#define PLAYER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QMap>
#include <QList>
#include <QFile>

struct PlayerStats
{
    QString hs_rate = "N/A";
    QString adr= "N/A";
    QString kdr= "N/A";
    QString hltv= "N/A";
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

    QString score = "N/A";
    QString mapName = "N/A";
    QString mapPic = "N/A";
};

double calculateHltv(const MatchStats& stats);
QJsonObject getJsonFromFile(const QString& filepath);

class Player
{
public:
    Player();
    void updateAccInfo(const QJsonObject& acc);
    void updateStats(const QJsonObject& stats);
    void updateMatches(const QList<QJsonObject>& matches);

    void print() const;
public:
    void updateLifetimeFromMatches();
    QMap <QString, QString> acc_info; // <variable name, value>
    PlayerStats lifetime_stats;
    QMap <QString,MatchStats> match_stats; // <match_id, stats>
};

#endif // PLAYER_H
