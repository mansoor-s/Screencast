#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QDesktopWidget>

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
    void rollOutBottom(int height = 450);
    void rollOutRight(int width = 950);
    void rollInRight();
    void setindicator(int pos);

public slots:

    void showDisplayPage();
    void showAudioPage();
    void showCameraPage();
    void showSettingsPage();
    void showOutputPage();
    void showAboutPage();
    void toggleRight();

    
private:
    Ui::MainWindow *ui;
    int defaultHeight;
    int defaultWidth;

    int currIndicator;
    int prevIndicator;

    bool rolledOutRight;

    void buttonClicked(int pos);
};

#endif // MAINWINDOW_H
