#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    setWindowFlags(Qt::WindowCloseButtonHint);

    this->defaultHeight = this->height();
    this->defaultWidth = this->width();

    this->currIndicator = 0;
    this->prevIndicator = -1;

    this->rolledOutRight = false;

    QRect screenGeometry = QDesktopWidget().availableGeometry();
    QRect currGeometry = frameGeometry();
    setGeometry(screenGeometry.width() / 2 - currGeometry.width() / 2,
                            (screenGeometry.height() / 2 - currGeometry.height() / 2) - 100,
                            currGeometry.width(),
                            currGeometry.height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rollInBottom()
{
    QRect geometry = this->geometry();

    QPropertyAnimation *animationMin = new QPropertyAnimation(this, "minimumHeight");
    QPropertyAnimation *animationMax = new QPropertyAnimation(this, "maximumHeight");
    animationMin->setDuration(250);
    animationMin->setStartValue(geometry.height());
    animationMin->setEndValue(this->defaultHeight);

    animationMax->setDuration(250);
    animationMax->setStartValue(geometry.height());
    animationMax->setEndValue(this->defaultHeight);

    animationMin->start();
    animationMax->start();
}

void MainWindow::rollOutBottom(int height)
{
    QRect geometry = this->geometry();

    QPropertyAnimation *animationMin = new QPropertyAnimation(this, "minimumHeight");
    QPropertyAnimation *animationMax = new QPropertyAnimation(this, "maximumHeight");
    animationMin->setDuration(250);
    animationMin->setStartValue(geometry.height());
    animationMin->setEndValue(height);

    animationMax->setDuration(250);
    animationMax->setStartValue(geometry.height());
    animationMax->setEndValue(height);

    animationMin->start();
    animationMax->start();
}


void MainWindow::rollInRight()
{
    this->rolledOutRight = false;

    QRect geometry = this->geometry();

    QPropertyAnimation *animationMin = new QPropertyAnimation(this, "minimumWidth");
    QPropertyAnimation *animationMax = new QPropertyAnimation(this, "maximumWidth");
    animationMin->setDuration(250);
    animationMin->setStartValue(geometry.width());
    animationMin->setEndValue(this->defaultWidth);

    animationMax->setDuration(250);
    animationMax->setStartValue(geometry.width());
    animationMax->setEndValue(this->defaultWidth);

    animationMin->start();
    animationMax->start();
}

void MainWindow::toggleRight()
{
    if (this->rolledOutRight) {
        this->rollInRight();
    } else {
        this->rollOutRight();
    }
}


void MainWindow::rollOutRight(int width)
{
    this->rolledOutRight = true;

    QRect geometry = this->geometry();

    QPropertyAnimation *animationMin = new QPropertyAnimation(this, "minimumWidth");
    QPropertyAnimation *animationMax = new QPropertyAnimation(this, "maximumWidth");
    animationMin->setDuration(250);
    animationMin->setStartValue(geometry.width());
    animationMin->setEndValue(width);

    animationMax->setDuration(250);
    animationMax->setStartValue(geometry.width());
    animationMax->setEndValue(width);

    animationMin->start();
    animationMax->start();

}


void MainWindow::setindicator(int pos)
{
    int delta = pos - this->currIndicator;

    QRect indicatorGeometry = this->ui->indicator->geometry();

    int transitionTime;
    if (delta == 0) {
        return;
    } else if (delta < 0) {
        transitionTime = 25 * delta * -1;
    } else {
        transitionTime = 25 * delta;
    }

    QPropertyAnimation *animation = new QPropertyAnimation(this->ui->indicator, "geometry");

    animation->setStartValue(indicatorGeometry);
    animation->setEndValue(QRect(40 + (pos * 100), indicatorGeometry.top(), indicatorGeometry.width(), indicatorGeometry.height()));
    animation->setEasingCurve(QEasingCurve::OutQuad);

    animation->setDuration(transitionTime);

    animation->start();
    this->currIndicator = pos;

}


void MainWindow::showDisplayPage()
{
    buttonClicked(0);
}

void MainWindow::showAudioPage()
{
    buttonClicked(1);
}

void MainWindow::showCameraPage()
{
    buttonClicked(2);
}

void MainWindow::showOutputPage()
{
    buttonClicked(3);
}

void MainWindow::showSettingsPage()
{
    buttonClicked(4);
}

void MainWindow::showAboutPage()
{
    buttonClicked(5);
    rollOutRight();
}


void MainWindow::buttonClicked(int pos)
{
    this->rollOutBottom();
    this->setindicator(pos);
    this->ui->stackedWidget->setCurrentIndex(pos);

    if (this->prevIndicator == pos) {
        this->rollInBottom();
        this->rollInRight();
        this->prevIndicator = -1;
    } else {
        this->prevIndicator = this->currIndicator;
    }


}


