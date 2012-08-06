#include "Recorder.h"

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    ffmpeg = new QProcess;
}

Recorder::~Recorder()
{
    delete ffmpeg;
}




void Recorder::startRecording(RecordInfo info)
{
    QString params = info.getCommandLineParams();

    qDebug() << params;
    ffmpeg->start("ffmpeg", params.split(" "));


}

void Recorder::stopRecording()
{

    ffmpeg->terminate();

}

void Recorder::ffmpegFinished()
{
}
