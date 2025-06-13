#ifndef PLAYERINPUTPANEL_H
#define PLAYERINPUTPANEL_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class PlayerInputPanel;
}

class PlayerInputPanel : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInputPanel(QWidget *parent = nullptr);
    ~PlayerInputPanel();

    QString text() const;
    void keyPressEvent(QKeyEvent* event) override;
signals:
    void confirmed(const QString& nickname, bool isLast50);
private slots:
    void confirm();
private:
    Ui::PlayerInputPanel *ui;

private:
    PlayerInputPanel(const PlayerInputPanel&) = delete;
    PlayerInputPanel& operator=(const PlayerInputPanel&) = delete;
};

#endif // PLAYERINPUTPANEL_H
