#include "player.h"

Player::Player()
{

}

void Player::updateAccInfo(const QJsonObject& acc)
{

    acc_info.insert("nickname", acc.value("nickname").toString());
    acc_info.insert("player_id", acc.value("player_id").toString());
    acc_info.insert("avatar", acc.value("avatar").toString());
    qDebug() << acc.value("nickname").toString();

    auto cs2data = acc.value("games").toObject().value("cs2").toObject();
    QString elo = QString::number(cs2data.value("faceit_elo").toDouble());
    QString lvl = QString::number(cs2data.value("skill_level").toDouble());
    acc_info.insert("elo", elo);
    acc_info.insert("level", lvl);
}

void Player::updateStats(const QJsonObject &stats)
{
    PlayerStats lifetime;
    QJsonObject lf_stats = stats.value("lifetime").toObject();

    this->acc_info.insert("number_of_matches", lf_stats.value("Matches").toString());
    this->acc_info.insert("number_of_cs2_matches", lf_stats.value("Total Matches").toString());
    this->lifetime_stats.hs_rate = lf_stats.value("Average Headshots %").toString();
    this->lifetime_stats.adr = lf_stats.value("ADR").toString();
    this->lifetime_stats.kdr = lf_stats.value("Average K/D Ratio").toString();
}

void Player::updateMatches(const QList<QJsonObject> &matches)
{
// TODO data needs to be unpacked and saved to object
}

void Player::print()
{
    qDebug() << "$" << lifetime_stats.kdr << "$";
    qDebug() << "$" << lifetime_stats.adr << "$";
    qDebug() << "$" << lifetime_stats.kills << "$";
    for (QString& key : acc_info.keys()) {
        QString val = acc_info.value(key);
        qDebug() << key << " : " << val;
    }
}
