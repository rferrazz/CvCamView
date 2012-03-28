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

#ifndef CVCAMVIEW_H
#define CVCAMVIEW_H

#include <QtDeclarative/QDeclarativeItem>
#include <QPainter>
#include <QLabel>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "cvcamresolution.h"

class CvCamView : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CvCamView)
    Q_ENUMS(CameraState)
    Q_PROPERTY(int iplWidth READ iplWidth)
    Q_PROPERTY(int iplHeight READ iplHeight)
    Q_PROPERTY(QByteArray iplData READ iplData NOTIFY newFrame)
    Q_PROPERTY(QImage qImage READ qImage NOTIFY newFrame)
    Q_PROPERTY(int camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(CvCamResolution *resolution READ resolution WRITE setResolution)
    //TODO: mettere a posto sti stati
    Q_PROPERTY(CameraState cameraState READ cameraState WRITE setCameraState NOTIFY cameraStateChanged)
    
public:
    CvCamView(QDeclarativeItem *parent = 0);
    ~CvCamView();
    static QImage ipl2Qimg(IplImage* iplImg);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    //enum
    enum CameraState {UnloadedState, LoadedState, ActiveState};

    //SET methods
    void setCamera(int camera);
    void setResolution(CvCamResolution *resolution);
    void setCameraState(CameraState state);

    //GET methods
    int iplWidth() const {return _iplImage->width;}
    int iplHeight() const {return _iplImage->height;}
    QByteArray iplData() const {return QByteArray(_iplImage->imageData, _iplImage->imageSize);}
    QImage qImage() const {return _qImage;}
    int camera() const {return _camera;}
    CvCamResolution *resolution() const {return _resolution;}
    CameraState cameraState() const {return _cameraState;}

signals:
    void newFrame();
    void cameraChanged();
    void cameraStateChanged();

private:
    IplImage* _iplImage;
    QImage _qImage;
    int _camera;
    CvCamResolution *_resolution;
    CameraState _cameraState;
    CvCapture *capture;
    QTimer *timer;
    void setupCamera();
    void decreaseCameraState();
    void increaseCameraState();

private slots:
    void queryFrame();
};

QML_DECLARE_TYPE(CvCamView)

#endif // CVCAMVIEW_H

