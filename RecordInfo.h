#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QString>

class RecordInfo
{
public:

    enum ScreenCapturetype {
        FullScreen,
        SelectedRegion,
        Window
    };

    enum AudioSource {
        Microphone,
        System
    };


    enum OutputContainers {
        OGG,
        MKV,
        AVI,
        MP4
    };

    enum AudioCodecs {
        FLAC,
        ALAC,
        MP3,
        AAC
    };

    enum VideoCodecs {
        X256,
        AMV,
        H261,
        MPEG4,
        THEORA
    };


    bool audioEnabled = true;
    QString screenCaptureType;
    QString audioSource;
    QString audioCodec;
    QString outputContainer;
    QString videoCodec;

    QString filePath;

    QString resolution;
    QString preset = "";

    //constructor
    RecordInfo() {

    }


    void setVideoCodec(RecordInfo::VideoCodecs codec) {
        switch(codec) {
        case RecordInfo::X256:
            videoCodec = "libx256";
            break;
        case RecordInfo::AMV:
            videoCodec = "amv";
            break;
        case RecordInfo::H261:
            videoCodec = "h261";
            break;
        case RecordInfo::MPEG4:
            videoCodec = "mpeg4";
            break;
        case RecordInfo::THEORA:
            videoCodec = "libtheora";
            break;
        }
    }

    void setAudioCodec(RecordInfo::AudioCodecs codec) {
        switch(codec) {
        case RecordInfo::FLAC:
            audioCodec = "flac";
            break;
        case RecordInfo::ALAC:
            audioCodec = "alac";
            break;
        case RecordInfo::MP3:
            audioCodec = "libmp3lame";
            break;
        case RecordInfo::AAC:
            audioCodec = "aac";
            break;
        }
    }

    void setOutputContainer(int container) {

        switch(container) {
        case RecordInfo::OGG:
            outputContainer = "ogg";
            break;
        case RecordInfo::MKV:
            outputContainer = "mkv";
            break;
        case RecordInfo::AVI:
            outputContainer = "avi";
            break;
        case RecordInfo::MP4:
            outputContainer = "mp4";
            break;
        }
    }

    void setOutputFileName(QString file) {
        filePath = file;
    }


    void setAudioEnabled(bool enabled = true) {
        audioEnabled = enabled;
    }

    void setAudioSource(RecordInfo::AudioSource source) {
        switch(source) {
        case RecordInfo::Microphone:
            audioSource = "";
        case RecordInfo::System:
            audioSource = "pulse";
        }
    }

    void setResolution(QString rez) {
        resolution = rez;
    }

    //return the entire command
    QString getCommandLineParams() {

        QString output = "-f x11grab -s " + resolution + " -r 30 -i :0 ";
        output += "-f alsa -ac 2 -ab 192k -i pulse ";

        output += "-acodec libmp3lame -vcodec libx264 -preset ultrafast -threads 0 ";

        output += filePath;


        return output;
    }

};

#endif // RECORDINFO_H
