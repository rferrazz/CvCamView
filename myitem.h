#ifndef MYITEM_H
#define MYITEM_H

#include <QtDeclarative/QDeclarativeItem>
#include "camthread.h"
#include <opencv/cv.h>

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

protected:
    IplImage* iplImage;
    QImage qImage;
    int camera;

private:
    CamThread* camThread;
};

QML_DECLARE_TYPE(MyItem)

#endif // MYITEM_H

