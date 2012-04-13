#include "cvhaardetector.h"

CvHaarDetector::CvHaarDetector(QObject *parent) :
    QObject(parent)
{
    storage = cvCreateMemStorage(0);
    _scaleFactor = 1.1;
    _minNeighbors = 3;
    _method = HaarCannyPruning;
    setClassifier("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml");
}

CvHaarDetector::~CvHaarDetector(){
    cvReleaseMemStorage(&storage);
    //delete _classifier;
}

void CvHaarDetector::setClassifier(QString classifier){
    currentClassifier = classifier;
    _classifier = cvLoadHaarClassifierCascade(classifier.toAscii().data(), cvSize(0,0));
}

void CvHaarDetector::setScaleFactor(double scaleFactor){
    _scaleFactor = scaleFactor;
}

void CvHaarDetector::setMinNeighbors(int minNeighbors){
    _minNeighbors = minNeighbors;
}

void CvHaarDetector::setMethod(HaarMethod method){
    _method = method;
}

void CvHaarDetector::haarDetect(QByteArray imageData, int imageWidth, int imageHeight){
    IplImage *image = cvCreateImage(cvSize(imageWidth, imageHeight), IPL_DEPTH_8U, 3);
    cvSetData(image, imageData.data(), imageWidth*3);
    cvClearMemStorage(storage);
    _results = cvHaarDetectObjects(image, _classifier, storage, _scaleFactor, _minNeighbors, _method);
    emit resultsReady();
}

QVariantList CvHaarDetector::results(){
    QVariantList res;
    for(int i=0; i<_results->total; i++){
        QMap<QString, QVariant> map;
        CvRect *r = (CvRect*)cvGetSeqElem(_results, i);
        map.insert("x", r->x);
        map.insert("y", r->y);
        map.insert("width", r->width);
        map.insert("height", r->height);
        res.append(map);
    }
    return res;
}
