#ifndef CAMTHREAD_H
#define CAMTHREAD_H

#include <QThread>
#include <QLabel>
#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "libraries/qtcvutils.h"

class CamThread : public QThread
{
    Q_OBJECT
public:
    explicit CamThread(int camera, bool calibrated, QObject *parent = 0);
    ~CamThread();

private:
    CvCapture* capture;
    static QImage ipl2Qimg(IplImage* iplImg);

protected:
    void run();

signals:
    void imageChanged(IplImage *newIpl, QImage newQImg);

public slots:

};

#endif // CAMTHREAD_H
