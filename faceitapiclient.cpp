#include "faceitapiclient.h"


FaceitApiClient::FaceitApiClient(const QString& key, QObject *parent)
    : QObject{parent}, apiKey{new QString{key}},
    manager{new QNetworkAccessManager{this}}, currentReply{nullptr}
{

}

void FaceitApiClient::fetchData(const QString& urlStr, const QMap<QString, QString>& params)
{
    QUrl url{urlStr};
    QUrlQuery query;
    for (QString param : params.keys()) {
        query.addQueryItem(param, params.value(param));
    }
    url.setQuery(query);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(*apiKey).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    currentReply = manager->get(request);
    connect(currentReply, &QNetworkReply::finished, this, &FaceitApiClient::replayReady);
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
            qDebug() << "ERROR1";
            qDebug() << currentReply->errorString();
            emit apiError(currentReply->errorString());
        }
        currentReply->deleteLater();
        currentReply = nullptr;
    }
    else {
        qDebug() << "ERROR2";
        QString errorMsg;
        QNetworkReply::NetworkError error = currentReply->error();
        switch (error)
        {
            case QNetworkReply::HostNotFoundError:
                errorMsg = "No internet connection";
                break;
            case QNetworkReply::TimeoutError:
                errorMsg = "Timed out";
                break;
            case QNetworkReply::ContentNotFoundError:
                errorMsg = "Invalid nickname";
                break;
            case QNetworkReply::AuthenticationRequiredError:
                errorMsg = "Invalid api key";
                break;
            case QNetworkReply::ContentAccessDenied:
                errorMsg = "Access denied";
                break;
            default:
                int httpStatus = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                qDebug() << "!!! " << httpStatus << " !!!";
                if (httpStatus == 400) {
                    errorMsg = "Unknown Error\nMake sure your\napi key is valid";
                    break;
                }
                qDebug() <<QString("Network error: %1").arg(currentReply->errorString());
                errorMsg = "Unknown error";
                break;
        }
        qDebug() << errorMsg;
        emit apiError(errorMsg);
    }
}

QJsonObject FaceitApiClient::getLastResponse() const
{
    return lastResponse;
}
