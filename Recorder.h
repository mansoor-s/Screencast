#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QProcess>
#include <QDebug>

#include "RecordInfo.h"


class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent = 0);
    ~Recorder();

    void startRecording(RecordInfo info);
    void stopRecording();

public slots:
    void ffmpegFinished();

private:
    QProcess *ffmpeg;
    
};

#endif // RECORDER_H
