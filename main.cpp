#include "playerstatswindow.h"

#include <QApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

QString PATH_TO_KEY = "../../key.txt";

QString loadApiKety(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file:" << filename;
        return "";
    }

    QTextStream in(&file);
    QString apiKey = in.readAll();
    file.close();

    apiKey.remove("\n");
    return apiKey;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerStatsWindow w;
    qDebug() << "Current working dir:" << QDir::currentPath();

    QString apiKey = loadApiKety(PATH_TO_KEY);
    qDebug() << apiKey;
    return 0;
    return a.exec();
}
