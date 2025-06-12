#ifndef MATCHSTATSWIDGET_H
#define MATCHSTATSWIDGET_H

#include <QWidget>

namespace Ui {
class MatchStatsWidget;
}

class MatchStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchStatsWidget(QWidget *parent = nullptr);
    ~MatchStatsWidget();

private:
    Ui::MatchStatsWidget *ui;
};

#endif // MATCHSTATSWIDGET_H
