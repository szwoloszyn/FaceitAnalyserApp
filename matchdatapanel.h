#ifndef MATCHDATAPANEL_H
#define MATCHDATAPANEL_H

#include <QWidget>

namespace Ui {
class MatchDataPanel;
}

class MatchDataPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MatchDataPanel(QWidget *parent = nullptr);
    ~MatchDataPanel();

private:
    Ui::MatchDataPanel *ui;
};

#endif // MATCHDATAPANEL_H
