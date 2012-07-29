#include "Recorder.h"

Recorder::Recorder()
{
    ffmpeg = new QProcess;
}

Recorder::~Recorder()
{
    delete ffmpeg;
}




void Recorder::startRecording(RecordInfo info)
{
    QString command = info.outputCommand();


}

void Recorder::stopRecording()
{

}
