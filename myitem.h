#ifndef MYITEM_H
#define MYITEM_H

#include <QtDeclarative/QDeclarativeItem>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class MyItem : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MyItem)
    Q_PROPERTY(IplImage* iplImage READ iplImage NOTIFY newFrame)
    Q_PROPERTY(QImage qImage READ qImage NOTIFY newFrame)
    Q_PROPERTY(int camera READ camera WRITE setCamera NOTIFY cameraChanged)
    
public:
    MyItem(QDeclarativeItem *parent = 0);
    ~MyItem();
    static QImage ipl2Qimg(IplImage* iplImg);

    //SET methods
    void setCamera(int camera);

    //GET methods
    IplImage* iplImage() const {return _iplImage;}
    QImage qImage() const {return _qImage;}
    int camera() const {return _camera;}

signals:
    void newFrame();
    void cameraChanged();

protected:
    void setupCamera();
    IplImage* _iplImage;
    QImage _qImage;
    int _camera;

private:
    QLabel* label;
    QGraphicsProxyWidget* widget;
    CvCapture *capture;

private slots:
    void queryFrame();
};

QML_DECLARE_TYPE(MyItem)

#endif // MYITEM_H

