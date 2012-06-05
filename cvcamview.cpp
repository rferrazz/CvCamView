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

#include "cvcamview.h"

#include <QtDeclarative/qdeclarative.h>
#include <QTimer>

CvCamView::CvCamView(QDeclarativeItem *parent):
    QDeclarativeItem(parent), _camera(0), _resolution(new CvCamResolution()), _cameraState(UnloadedState)
{
    setFlag(ItemHasNoContents, false);
    capture = NULL;
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(queryFrame()));
    timer->start(40);
    setupCamera();
}

void CvCamView::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget){
    QSize imageSize = _qImage.size();
    imageSize.scale(boundingRect().width(), boundingRect().height(), Qt::KeepAspectRatio);
    QRect ImgBoundingRect((boundingRect().width()/2)-(imageSize.width()/2),
                          (boundingRect().height()/2)-(imageSize.height()/2), imageSize.width(), imageSize.height());
    painter->drawImage(ImgBoundingRect, _qImage, _qImage.rect());
}

void CvCamView::setCamera(int camera){
    this->_camera = camera;
    setupCamera();
    emit cameraChanged();
}

void CvCamView::setResolution(CvCamResolution *resolution){
    _resolution = resolution;
    setupCamera();
}

void CvCamView::setCameraState(CameraState state){
    while(state < _cameraState)
        decreaseCameraState();
    while(state > _cameraState)
        increaseCameraState();
}

void CvCamView::increaseCameraState(){
    int state = ((int)_cameraState)+1;
    switch(state){
    case LoadedState:
        capture = cvCreateCameraCapture(_camera);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, _resolution->width());
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, _resolution->height());
        break;
    case ActiveState:
        timer->blockSignals(false);
        break;
    }
    _cameraState = (CameraState)state;
    emit cameraStateChanged();
}

void CvCamView::decreaseCameraState(){
    int state = ((int)_cameraState)-1;
    switch(state){
    case LoadedState:
        timer->blockSignals(true);
        break;
    case UnloadedState:
        cvReleaseCapture(&capture);
        break;
    }
    _cameraState = (CameraState)state;
    emit cameraStateChanged();
}

void CvCamView::setupCamera(){
    setCameraState(UnloadedState);
    setCameraState(ActiveState);
}

void CvCamView::queryFrame(){
    _iplImage = cvQueryFrame(capture);
    _qImage = CvCamView::ipl2Qimg(_iplImage);
    update();
    emit newFrame();
}

CvCamView::~CvCamView()
{
    cvReleaseCapture(&capture);
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


