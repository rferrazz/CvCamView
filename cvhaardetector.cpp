#include "cvhaardetector.h"
#include "QResource"

CvHaarDetector::CvHaarDetector(QObject *parent) :
    QObject(parent)
{
    storage = cvCreateMemStorage(0);
    _classifier = cvLoadHaarClassifierCascade("haarcascades/haarcascade_frontalface_default.xml");
}
