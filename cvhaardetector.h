#ifndef CVHAARDETECTOR_H
#define CVHAARDETECTOR_H

#include <QObject>
#include <opencv/cv.h>

class CvHaarDetector : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CvHaarDetector)
    Q_ENUMS(HaarMethod)
    Q_PROPERTY(QString classifier WRITE setClassifier)
    Q_PROPERTY(double scaleFactor READ scaleFactor WRITE setScaleFactor)
    Q_PROPERTY(int minNeighbors READ minNeighbors WRITE setMinNeighbors)
    Q_PROPERTY(HaarMethod method READ method WRITE setMethod)
    Q_PROPERTY(QVariant results READ results NOTIFY resultsReady)

public:
    explicit CvHaarDetector(QObject *parent = 0);
    enum HaarMethod {HaarScaleImage = CV_HAAR_SCALE_IMAGE,
                     HaarRoughSearch = CV_HAAR_DO_ROUGH_SEARCH,
                     HaarCannyPruning = CV_HAAR_DO_CANNY_PRUNING,
                     HaarFeatureMax = CV_HAAR_FEATURE_MAX,
                     HaarBiggestObject = CV_HAAR_FIND_BIGGEST_OBJECT
                    };
    
signals:
    void resultsReady();
    
public slots:
    void haarDetect(QByteArray imageData, int imageWidth, int imageHeight);

private:
    CvMemStorage *storage;
    CvSeq *_results;
    CvHaarClassifier *_classifier;
    double _scaleFactor;
    int _minNeighbors;
    HaarMethod _method;
    
};

#endif // CVHAARDETECTOR_H
