#include "myitem.h"

#include <QtDeclarative/qdeclarative.h>
#include <QTimer>

MyItem::MyItem(QDeclarativeItem *parent):
    QDeclarativeItem(parent), _camera(0)
{
    setFlag(ItemHasNoContents, false);
    label = new QLabel();
    widget = new QGraphicsProxyWidget(this);
    widget->setWidget(label);
    setupCamera();
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(queryFrame()));
    timer->start(40);
}

void MyItem::setCamera(int camera){
    this->_camera = camera;
    setupCamera();
    emit cameraChanged();
}

void MyItem::setupCamera(){
    capture = cvCreateCameraCapture(_camera);
}

void MyItem::queryFrame(){
    _iplImage = cvQueryFrame(capture);
    cvFlip(_iplImage,_iplImage, 1);
    _qImage = MyItem::ipl2Qimg(_iplImage);
    label->setPixmap(QPixmap::fromImage(_qImage.scaledToHeight(label->height())));
    emit newFrame();
}

MyItem::~MyItem()
{
}

QImage MyItem::ipl2Qimg(IplImage* iplImg){
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


