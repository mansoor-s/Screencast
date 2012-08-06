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

    this->recordingStarted = false;

    //set default hotkey to F10
    this->ui->recordHotkey->setCurrentIndex(4);

    //create system tray icon
    this->systrayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icons/icons/logo32.png");
    this->systrayIcon->setIcon(icon);

    connect(systrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(sysTrayActivated(QSystemTrayIcon::ActivationReason)));


    countdown = new Countdown();
    connect(countdown, SIGNAL(countdownFinished()), SLOT(countdownFinished()));


    //Setup default global start/stop recording shortcut
    globalShortcut = new QxtGlobalShortcut(this);
    connect(globalShortcut, SIGNAL(activated()), SLOT(globalShortcutActivated()));
    globalShortcut->setShortcut(QKeySequence("F10"));

    connect(this->ui->recordHotkey, SIGNAL(currentIndexChanged(QString)), SLOT(globalShortcutChanged(QString)));

    //be able to stop countdown
    connect(this, SIGNAL(stopCountdown()), countdown, SLOT(stop()));

    //start/stop recording
    recorder = new Recorder();

    outputFileName = "Screencast-" + QDateTime::currentDateTime().toString("yyyy-MMM-dd-h-m");

    outputDirectory = QDir::homePath();
    this->ui->outputDirlabel->setText(outputDirectory);


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
    animationMin->setDuration(75);
    animationMin->setStartValue(geometry.height());
    animationMin->setEndValue(this->defaultHeight);

    animationMax->setDuration(75);
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
    animationMin->setDuration(75);
    animationMin->setStartValue(geometry.height());
    animationMin->setEndValue(height);

    animationMax->setDuration(75);
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
    animationMin->setDuration(75);
    animationMin->setStartValue(geometry.width());
    animationMin->setEndValue(this->defaultWidth);

    animationMax->setDuration(75);
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

void MainWindow::sysTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (this->isVisible()) {
            this->hide();
        } else {
            //we are recording and we want to end it.
            this->show();
            this->systrayIcon->hide();

            if (recordingStarted) {
                recorder->stopRecording();
                recordingStarted = false;

            }
        }
    }

}

//start recording
void MainWindow::countdownFinished()
{
    qDebug() << "countdown finished!";



    RecordInfo info = readUI();
    recorder->startRecording(info);



}

void MainWindow::globalShortcutActivated()
{
    if (this->recordingStarted == true) {
        //incase it is still counting down and actual recording has not yet started
        emit stopCountdown();
        emit stopRecording();
        return;
    }


    this->recordingStarted = true;
    this->hide();
    this->systrayIcon->show();
    this->countdown->startCountdown(this->ui->recordingStartDelay->value());

}

//Recorder is letting us know that ffmpeg has stoped
void MainWindow::recordingFinished()
{
    qDebug() << "recording finished!";
    this->recordingStarted = false;
    this->show();
    this->systrayIcon->hide();
}

void MainWindow::setOutputDirectory()
{
    outputDirectory = QFileDialog::getExistingDirectory(this, "Choose output directory", QDir::homePath(), QFileDialog::ShowDirsOnly);

    this->ui->outputDirlabel->setText(outputDirectory);
}

RecordInfo MainWindow::readUI()
{
    RecordInfo info;

    //audio codec
    info.setAudioCodec((RecordInfo::AudioCodecs) ui->audioCodecCombo->currentIndex());

    //video codec
    info.setVideoCodec((RecordInfo::VideoCodecs)ui->videoCodecCombo->currentIndex());

    //container
    info.setOutputContainer(ui->outputContainerCombo->currentIndex());

    //audio source


    //filepath
    info.setOutputFileName(outputDirectory + "/" + outputFileName);

    //screen resolution
    info.setResolution(getScreenResolution());

    return info;

}


//change the shortcut we are listening on
void MainWindow::globalShortcutChanged(const QString &shortcut)
{
    globalShortcut->setShortcut(QKeySequence(shortcut));
}




void MainWindow::rollOutRight(int width)
{
    this->rolledOutRight = true;

    QRect geometry = this->geometry();

    QPropertyAnimation *animationMin = new QPropertyAnimation(this, "minimumWidth");
    QPropertyAnimation *animationMax = new QPropertyAnimation(this, "maximumWidth");
    animationMin->setDuration(75);
    animationMin->setStartValue(geometry.width());
    animationMin->setEndValue(width);

    animationMax->setDuration(75);
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


/*
    make the main window visible and center it on the screen
*/
void MainWindow::show()
{
    this->setVisible(true);
    QRect screenGeometry = QDesktopWidget().availableGeometry();
    QRect currGeometry = frameGeometry();
    setGeometry(screenGeometry.width() / 2 - currGeometry.width() / 2,
                            (screenGeometry.height() / 2 - currGeometry.height() / 2) - 100,
                            currGeometry.width(),
                currGeometry.height());
}

QString MainWindow::getScreenResolution()
{
    QProcess proc;
    QStringList args;
    args << "-c";
    args << "xrandr | grep '*' | awk '{print $1}'";
    //args << "xwininfo -root | grep 'geometry'| awk '{print $2;}'";
    proc.start("/bin/sh", args);

    proc.waitForFinished();

    return proc.readAll().trimmed();
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


/*
    One of the navigation button is clicked
*/
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


