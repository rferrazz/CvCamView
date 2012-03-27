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

#include "cvcamresolution.h"

CvCamResolution::CvCamResolution(QObject *parent) :
    QObject(parent), _width(640), _height(480)
{
}

CvCamResolution::~CvCamResolution(){}

void CvCamResolution::setWidth(int width){
    _width = width;
}

void CvCamResolution::setHeight(int height){
    _height = height;
}
