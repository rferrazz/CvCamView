#ifndef CVHAARDETECTOR_H
#define CVHAARDETECTOR_H

#include <QObject>
#include <QVariantList>
#include <QRect>
#include <opencv/cv.h>

class CvHaarDetector : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CvHaarDetector)
    Q_ENUMS(HaarMethod)
    Q_PROPERTY(QString classifier READ classifier WRITE setClassifier)
    Q_PROPERTY(double scaleFactor READ scaleFactor WRITE setScaleFactor)
    Q_PROPERTY(int minNeighbors READ minNeighbors WRITE setMinNeighbors)
    Q_PROPERTY(HaarMethod method READ method WRITE setMethod)
    Q_PROPERTY(QVariantList results READ results NOTIFY resultsReady)

public:
    explicit CvHaarDetector(QObject *parent = 0);
    ~CvHaarDetector();
    enum HaarMethod {HaarScaleImage = CV_HAAR_SCALE_IMAGE,
                     HaarRoughSearch = CV_HAAR_DO_ROUGH_SEARCH,
                     HaarCannyPruning = CV_HAAR_DO_CANNY_PRUNING,
                     HaarFeatureMax = CV_HAAR_FEATURE_MAX,
                     HaarBiggestObject = CV_HAAR_FIND_BIGGEST_OBJECT
                    };
    //SET methods
    void setClassifier(QString classifier);
    void setScaleFactor(double scaleFactor);
    void setMinNeighbors(int minNeighbors);
    void setMethod(HaarMethod method);

    //GET methods
    QString classifier() const {return currentClassifier;}
    double scaleFactor() const {return _scaleFactor;}
    int minNeighbors() const {return _minNeighbors;}
    HaarMethod method() const {return _method;}
    QVariantList results();

signals:
    void resultsReady();
    
public slots:
    void haarDetect(QByteArray imageData, int imageWidth, int imageHeight);

private:
    CvMemStorage *storage;
    CvSeq *_results;
    CvHaarClassifierCascade *_classifier;
    QString currentClassifier;
    double _scaleFactor;
    int _minNeighbors;
    HaarMethod _method;
    
};

#endif // CVHAARDETECTOR_H
