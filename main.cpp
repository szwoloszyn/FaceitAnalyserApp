#include <QApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

#include "mainwindow.h"


QString PATH_TO_KEY = "../../key.txt";

QString loadApiKey(const QString &filename)
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
    qDebug() << "Current working dir:" << QDir::currentPath();

    QString apiKey = loadApiKey(PATH_TO_KEY);
    qDebug() << apiKey;
    MainWindow w{apiKey};
    w.show();
    return a.exec();
}
