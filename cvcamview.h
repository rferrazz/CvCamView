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
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "cvcamresolution.h"

class CvCamView : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CvCamView)
    Q_PROPERTY(IplImage* iplImage READ iplImage NOTIFY newFrame)
    Q_PROPERTY(QImage qImage READ qImage NOTIFY newFrame)
    Q_PROPERTY(int camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(CvCamResolution *resolution READ resolution WRITE setResolution)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    
public:
    CvCamView(QDeclarativeItem *parent = 0);
    ~CvCamView();
    static QImage ipl2Qimg(IplImage* iplImg);

    //SET methods
    void setCamera(int camera);
    void setResolution(CvCamResolution *resolution);
    void setWidth(int width);
    void setHeight(int height);

    //GET methods
    IplImage* iplImage() const {return _iplImage;}
    QImage qImage() const {return _qImage;}
    int camera() const {return _camera;}
    CvCamResolution *resolution() const {return _resolution;}
    int width() const {return label->width();}
    int height() const {return label->height();}

signals:
    void newFrame();
    void cameraChanged();
    void widthChanged();
    void heightChanged();

private:
    void setupCamera();
    IplImage* _iplImage;
    QImage _qImage;
    int _camera;
    CvCamResolution *_resolution;
    QLabel* label;
    QGraphicsProxyWidget* widget;
    CvCapture *capture;
    QTimer *timer;

private slots:
    void queryFrame();
};

QML_DECLARE_TYPE(CvCamView)

#endif // CVCAMVIEW_H

