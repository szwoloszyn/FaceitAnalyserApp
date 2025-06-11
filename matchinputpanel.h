#ifndef MATCHINPUTPANEL_H
#define MATCHINPUTPANEL_H

#include <QWidget>

namespace Ui {
class MatchInputPanel;
}

class MatchInputPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MatchInputPanel(QWidget *parent = nullptr);
    ~MatchInputPanel();

    QString text() const;
    void keyPressEvent(QKeyEvent* event) override;
signals:
    void confirmed(const QString& match_id);
private slots:
    void confirm();

private:
    Ui::MatchInputPanel *ui;
};

#endif // MATCHINPUTPANEL_H
