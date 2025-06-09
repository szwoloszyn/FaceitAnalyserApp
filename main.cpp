#include "playerstatsmanager.h"
#include "playerinputpanel.h"
#include "playerdatapanel.h"
#include "playerstatswidget.h"
#include "mainwindow.h"
#include "machine.h"

#include <QApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

#ifdef THINKPAD
QString PATH_TO_KEY = "../FaceitAnalyserApp/key.txt";
#else
QString PATH_TO_KEY = "../../key.txt";
#endif
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
    //PlayerStatsManager w(apiKey);
    MainWindow w{apiKey};
    w.show();
    return a.exec();
}
