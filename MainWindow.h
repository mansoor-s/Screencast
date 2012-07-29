#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QSystemTrayIcon>
#include <QxtGui/QxtGlobalShortcut>
#include <QFileDialog>
#include <QDateTime>
#include <QProcess>


#include "Countdown.h"
#include "Recorder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void rollInBottom();
    void rollOutBottom(int height = 470);
    void rollOutRight(int width = 950);
    void rollInRight();
    void setindicator(int pos);
    void show();
    QString getScreenResolution();




signals:
    void stopCountdown();
    void startRecording(RecordInfo);
    void stopRecording();


public slots:

    void showDisplayPage();
    void showAudioPage();
    void showCameraPage();
    void showSettingsPage();
    void showOutputPage();
    void showAboutPage();
    void toggleRight();

    void sysTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void countdownFinished();

    void globalShortcutChanged(const QString &shortcut);
    void globalShortcutActivated();

    void recordingFinished();

    void setOutputDirectory();
    
private:
    Ui::MainWindow *ui;
    int defaultHeight;
    int defaultWidth;

    int currIndicator;
    int prevIndicator;

    bool rolledOutRight;

    void buttonClicked(int pos);

    QSystemTrayIcon *systrayIcon;

    QxtGlobalShortcut *globalShortcut;

    bool recordingStarted;

    Countdown *countdown;

    Recorder *recorder;

    QString outputFileName;
    QString outputDirectory;
};

#endif // MAINWINDOW_H
