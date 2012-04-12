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

#ifndef CVCAMRESOLUTION_H
#define CVCAMRESOLUTION_H

#include <QObject>

class CvCamResolution : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CvCamResolution)
    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(int height READ height WRITE setHeight)

public:
    CvCamResolution(QObject *parent = 0);
    ~CvCamResolution();

    enum haarMethod {};
    
    //SET methods
    void setWidth(int width);
    void setHeight(int height);

    //GET methods
    int width() const {return _width;}
    int height() const {return _height;}

private:
    int _width;
    int _height;
    
};

//QML_DECLARE_TYPE(CvCamResolution)

#endif // CVCAMRESOLUTION_H
