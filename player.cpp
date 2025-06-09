#include "player.h"

Player::Player()
{

}

void Player::updateAccInfo(const QJsonObject& acc)
{

    acc_info.insert("nickname", acc.value("nickname").toString());
    acc_info.insert("player_id", acc.value("player_id").toString());
    acc_info.insert("avatar", acc.value("avatar").toString());

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

void Player::updateMatches(const QList<QJsonObject> &matchesResponse)
{
    for (QJsonObject matchResponse : matchesResponse) {
        QJsonArray matches = matchResponse.value("items").toArray();
        for (const QJsonValue& matchVal : matches) {

            QJsonObject match = matchVal.toObject().value("stats").toObject();

            MatchStats stats;
            stats.adr = match.value("ADR").toString().toDouble();
            stats.kdr = match.value("K/D Ratio").toString().toDouble();
            stats.kpr = match.value("K/R Ratio").toString().toDouble();
            stats.kills = match.value("Kills").toString().toInt();
            stats.assists = match.value("Assists").toString().toInt();
            stats.deaths = match.value("Deaths").toString().toInt();

            stats.double_kills = match.value("Double Kills").toString().toInt();
            stats.triple_kills = match.value("Triple Kills").toString().toInt();
            stats.quad_kills = match.value("Quadro Kills").toString().toInt();
            stats.aces = match.value("Penta Kills").toString().toInt();

            stats.rounds = match.value("Rounds").toString().toInt();
            stats.hltv = calculateHltv(stats);
            // WARNING it corrupts match id
            QString match_id = match.value("Match Id").toString();
            while (match_stats.contains(match_id)) {
                match_id += "_nmap";
            }
            this->match_stats.insert(match_id, stats);

            // printing one random match for debug
            // if (match.value("Match Id").toString() == "1-7bab85e5-3d81-40d2-9f40-21cb87f671f1") {
            //     qDebug() << "rounds: " << stats.rounds << " $ "
            //              << "kills: " << stats.kills << " $ "
            //              << "deaths: " << stats.deaths
            //              << "2x 3x 4x 5x" << stats.double_kills << " " << stats.triple_kills << " " << stats.quad_kills
            //              << "kpr" << stats.kpr
            //              << "map: " << match.value("Map").toString()
            //              << "match id: " << match.value("Match Id").toString();
            //     qDebug() << "hltv: " << stats.hltv;
            // }
        }
    }
}

void Player::updateLifetimeFromMatches()
{
    if (match_stats.size() < qMin(50,acc_info.value("number_of_cs2_matches").toInt())) {
        qDebug() << match_stats.size() << " not enough matches on input. using default data";
        return;
    }
    double overallKDR = 0;
    double overallAdr = 0;
    double overallHltv = 0;
    for (auto stats : match_stats.values()) {
        overallKDR += stats.kdr;
        overallAdr += stats.adr;
        overallHltv += stats.hltv;
    }
    double avgKDR = overallKDR / match_stats.size();
    double avgADR = overallAdr / match_stats.size();
    double avgHLTV = overallHltv / match_stats.size();
    lifetime_stats.adr = QString::number(avgADR, 'f', 2);
    lifetime_stats.kdr = QString::number(avgKDR, 'f', 2);
    lifetime_stats.hltv = QString::number(avgHLTV);//, 'f', 2);
}

void Player::print() const
{
    qDebug() << "$" << lifetime_stats.kdr << "$";
    qDebug() << "$" << lifetime_stats.adr << "$";
    qDebug() << "$" << lifetime_stats.hltv << "$";
    qDebug() << "$" << lifetime_stats.hs_rate << "$";
    MatchStats a = match_stats.value("1-e36ed649-665a-460a-b668-c7cd1514f37e");
    qDebug() << "@" << a.kills << "@";
    qDebug() << "@" << a.assists << "@";
    qDebug() << "@" << a.hltv << "@";
    for (QString& key : acc_info.keys()) {
        QString val = acc_info.value(key);
        qDebug() << key << " : " << val;
    }
}



double calculateHltv(const MatchStats &stats)
{
    if (stats.rounds == 0) {
        qDebug() << "rounds not parsed error";
        return 0;
    }
    const double avgKPR = 0.679;
    const double avgSPR = 0.317;
    const double avgRMK = 1.277;

    double killRating = stats.kpr / avgKPR;
    double survivalRating = (double(stats.rounds - stats.deaths) / stats.rounds) / avgSPR;
    int single_kills = stats.kills - (2*stats.double_kills + 3*stats.triple_kills + 4*stats.quad_kills + 5*stats.aces);
    double roundsWithMultipleRating = (double(single_kills + 4*stats.double_kills +
                                              9*stats.triple_kills + 16*stats.quad_kills +
                                              25*stats.aces) / stats.rounds) / avgRMK;
    return (killRating + 0.7*survivalRating + roundsWithMultipleRating) / 2.7;
}
