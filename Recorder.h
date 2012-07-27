#ifndef RECORDER_H
#define RECORDER_H

#include <QThread>

class Recorder : public QThread
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // RECORDER_H
