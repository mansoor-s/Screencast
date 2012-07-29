#include "Countdown.h"
#include "ui_cowntdown.h"

Countdown::Countdown(QWidget *parent) : QDialog(parent),  ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());


    timer = new QTimer(this);
    timer->setInterval(1000);
    countdownRunning = false;
    currTick = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

Countdown::~Countdown()
{
    delete ui;
}

void Countdown::startCountdown(int seconds)
{
    if (seconds == 0) {
        emit countdownFinished();
        return;
    }

    this->ui->timer->setText(QString::number(seconds));
    this->show();

    totalTicks = seconds;
    countdownRunning = true;
    timer->start();
}

void Countdown::tick()
{
    currTick++;

    if (currTick == totalTicks) {
        stop();
        emit countdownFinished();
        return;
    }

    this->ui->timer->setText(QString::number(totalTicks - currTick));
}

void Countdown::stop()
{
    this->hide();
    this->timer->stop();
    countdownRunning = false;
    currTick = 0;
}
