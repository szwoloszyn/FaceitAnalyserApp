#ifndef FACEITAPICLIENT_H
#define FACEITAPICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>


class FaceitApiClient : public QObject
{
    Q_OBJECT
public:
    explicit FaceitApiClient(const QString& key, QObject *parent = nullptr);
    void fetchData(const QString& url, const QString& nickname = "");
    QJsonObject getLastResponse() const;

signals:
    void playerDataReady(const QJsonObject& json);
    void apiError(const QString& errorMessage);

private slots:
    void replayReady();

private:
    const QString* apiKey;
    QNetworkAccessManager* manager;
    QNetworkReply* currentReply;
    QJsonObject lastResponse;
};

#endif // FACEITAPICLIENT_H
