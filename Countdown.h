#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QDialog>
#include <QTimer>
#include <QDesktopWidget>

namespace Ui {
    class Dialog;
}

class Countdown : public QDialog
{
    Q_OBJECT
public:
    Countdown(QWidget *parent = 0);
    ~Countdown();

    bool startCountdown(int seconds = 0);

signals:
    void countdownFinished();

public slots:
    void tick();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    int currTick;
    int totalTicks;
    bool countdownRunning;
};

#endif // COUNTDOWN_H
