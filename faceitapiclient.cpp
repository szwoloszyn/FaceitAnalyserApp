#include "faceitapiclient.h"


FaceitApiClient::FaceitApiClient(const QString& key, QObject *parent)
    : QObject{parent}, apiKey{new QString{key}},
    manager{new QNetworkAccessManager{this}}, currentReply{nullptr}
{

}

void FaceitApiClient::fetchData(const QString& urlStr, const QMap<QString, QString>& params)
{
    qDebug() << urlStr;
    QUrl url{urlStr};
    QUrlQuery query;
    for (QString param : params.keys()) {
        query.addQueryItem(param, params.value(param));
    }
    url.setQuery(query);
    QNetworkRequest request;
    request.setUrl(url);
    //request.setRawHeader("Authorization", "Bearer " + apiKey.toUtf8());
    request.setRawHeader("Authorization", QString("Bearer %1").arg(*apiKey).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    currentReply = manager->get(request);
    connect(currentReply, &QNetworkReply::finished, this, &FaceitApiClient::replayReady);

    // connect(reply, &QNetworkReply::finished,
    //        this, &FaceitApiClient::replayReady);
}

void FaceitApiClient::replayReady()
{
    qDebug() << "start";
    if (currentReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = currentReply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (jsonDoc.isObject()) {

            this->lastResponse = jsonDoc.object();
            qDebug() << "FINE";
            emit playerDataReady(lastResponse);
        }
        else {
            qDebug() << "STUCK!!";
            qDebug() << currentReply->errorString();
            emit apiError(currentReply->errorString());
        }
        currentReply->deleteLater();
        currentReply = nullptr;
    }
    else {
        qDebug() << "STUCK HERE!!";
        QString errorMsg = QString("Network error: %1").arg(currentReply->errorString());
        qDebug() << errorMsg;
        emit apiError(errorMsg);
    }
}

QJsonObject FaceitApiClient::getLastResponse() const {
    return lastResponse;
}
