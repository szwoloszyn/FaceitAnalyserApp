#ifndef MATCHSTATSWIDGET_H
#define MATCHSTATSWIDGET_H

#include <QWidget>

#include "player.h"

namespace Ui {
class MatchStatsWidget;
}

class MatchStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchStatsWidget(QWidget *parent = nullptr);
    ~MatchStatsWidget();

    void setData(const MatchStats& match);
    void setCustomError(const QString& error);
    void setErrorFromPlayer();
signals:
    void dataRequested(const QString& match_id);
private slots:
    void requestData(const QString& match_id);
private:
    Ui::MatchStatsWidget *ui;

private:
    MatchStatsWidget(const MatchStatsWidget&) = delete;
    MatchStatsWidget& operator=(const MatchStatsWidget&) = delete;
};

#endif // MATCHSTATSWIDGET_H
