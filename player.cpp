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

void Player::print()
{
    for (QString& key : acc_info.keys()) {
        QString val = acc_info.value(key);
        qDebug() << key << " : " << val;
    }
}
