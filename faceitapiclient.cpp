#include "faceitapiclient.h"


FaceitApiClient::FaceitApiClient(const QString& key, QObject *parent)
    : QObject{parent}, apiKey{new QString{key}},
    manager{new QNetworkAccessManager{this}}, currentReply{nullptr}
{

}

void FaceitApiClient::fetchData(const QString& urlStr, const QString& nickname)
{
    const QUrl url{urlStr + nickname};
    QNetworkRequest request;
    request.setUrl(url);
    //request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());
    request.setRawHeader("Authorization", QString("Bearer %1").arg(*apiKey).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    currentReply = manager->get(request);
    connect(currentReply, &QNetworkReply::finished, this, &FaceitApiClient::replayReady);


    //connect(reply, &QNetworkReply::finished,
    //        this, &FaceitApiClient::replayReady);
}

void FaceitApiClient::replayReady()
{
    if (currentReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = currentReply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (jsonDoc.isObject()) {

            this->lastResponse = jsonDoc.object();
            emit playerDataReady(lastResponse);
        }
        else {
            emit apiError(currentReply->errorString());
        }
        currentReply->deleteLater();
        currentReply = nullptr;
    }
}

QJsonObject FaceitApiClient::getLastResponse() const {
    return lastResponse;
}
