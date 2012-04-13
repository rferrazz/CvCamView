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

#include "cvcamview_plugin.h"
#include "cvcamview.h"
#include "cvcamresolution.h"
#include "cvhaardetector.h"

#include <QApplication>
#include <QtDeclarative/qdeclarative.h>

void CvCamViewPlugin::registerTypes(const char *uri)
{
    // @uri opencv.components
    qmlRegisterType<CvCamResolution>(uri, 1, 0, "CvCamResolution");
    qmlRegisterType<CvCamView>(uri, 1, 0, "CvCamView");
    qmlRegisterType<CvHaarDetector>(uri, 1, 0, "CvHaarDetector");

}

Q_EXPORT_PLUGIN2(CvCamView, CvCamViewPlugin)
