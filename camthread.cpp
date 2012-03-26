#include "camthread.h"

CamThread::CamThread(int camera, QObject *parent) :
    QThread(parent)
{
    capture = cvCreateCameraCapture(camera);
    QThread::start();
}

CamThread::~CamThread(){
    cvReleaseCapture(&capture);
    QThread::terminate();
}

void CamThread::run(){
    while(1){
        IplImage* cvimage = cvQueryFrame(capture);
        cvFlip(cvimage, cvimage, 1);
        QImage image = ipl2Qimg(cvimage);
        emit imageChanged(cvimage, image);
    }
}

static QImage ipl2Qimg(IplImage* iplImg){
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage qimg(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1)
            {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4)
            {
                a = data[x * channels + 3];
                qimg.setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                qimg.setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qimg;
}
