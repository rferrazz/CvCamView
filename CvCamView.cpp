/*
Copyright (C) 2012 Riccardo Ferrazzo <f.riccardo87@gmail.com>

This file is part of CvCamView.

    CvCamView is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WebDomo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with CvCamView.  If not, see <http://www.gnu.org/licenses/>
*/

#include "CvCamView.h"

#include <QtDeclarative/qdeclarative.h>
#include <QTimer>

CvCamView::CvCamView(QDeclarativeItem *parent):
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

void CvCamView::setCamera(int camera){
    this->_camera = camera;
    setupCamera();
    emit cameraChanged();
}

void CvCamView::setWidth(int width){
    label->setFixedWidth(width);
    emit widthChanged();
}

void CvCamView::setHeight(int height){
    label->setFixedHeight(height);
    emit heightChanged();
}

void CvCamView::setupCamera(){
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 800);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 600);
    capture = cvCreateCameraCapture(_camera);
}

void CvCamView::queryFrame(){
    _iplImage = cvQueryFrame(capture);
    _qImage = CvCamView::ipl2Qimg(_iplImage);
    label->setPixmap(QPixmap::fromImage(_qImage.scaledToHeight(label->height())));
    emit newFrame();
}

CvCamView::~CvCamView()
{
}

QImage CvCamView::ipl2Qimg(IplImage* iplImg){
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


