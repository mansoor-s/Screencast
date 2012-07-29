#ifndef RECORDER_H
#define RECORDER_H

#include <QProcess>

#include "RecordInfo.h"


class Recorder
{
public:
    explicit Recorder();
    ~Recorder();

    void startRecording(RecordInfo info);
    void stopRecording();


private:
    QProcess *ffmpeg;
    
};

#endif // RECORDER_H
