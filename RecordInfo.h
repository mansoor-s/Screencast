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
        MPEG2
    };


    bool audioEnabled = true;
    QString screenCaptureType;
    QString audioSource;
    QString audioCodec;
    QString outputContainer;
    QString videoCodec;

    QString filePath;

    QString resolution;

    //constructor
    RecordInfo() {

    }

    void setVideoCodec(RecordInfo::VideoCodecs codec) {
        switch(codec) {
        case RecordInfo::X256:
            videoCodec = "x256";

        case RecordInfo::AMV:
            videoCodec = "amv";

        case RecordInfo::H261:
            videoCodec = "h261";

        case RecordInfo::MPEG2:
            videoCodec = "mpeg-2";
        }
    }

    void setAudioCodec(RecordInfo::AudioCodecs codec) {
        switch(codec) {
        case RecordInfo::FLAC:
            audioCodec = "flac";

        case RecordInfo::ALAC:
            audioCodec = "alac";

        case RecordInfo::MP3:
            audioCodec = "mp3";

        case RecordInfo::AAC:
            audioCodec = "aac";
        }
    }

    void setOutputContainer(RecordInfo::OutputContainers container) {

        switch(container) {
        case RecordInfo::OGG:
            outputContainer = "ogg";

        case RecordInfo::MKV:
            outputContainer = "mkv";

        case RecordInfo::AVI:
            outputContainer = "avi";

        case RecordInfo::MP4:
            outputContainer = "mp4";
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
    QString outputCommand() {
        return "";
    }

};

#endif // RECORDINFO_H
