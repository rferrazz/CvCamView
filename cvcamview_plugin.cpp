#include "cvcamview_plugin.h"
#include "myitem.h"

#include <QApplication>
#include <QtDeclarative/qdeclarative.h>

void CvCamViewPlugin::registerTypes(const char *uri)
{
    // @uri com.ferrazz.qmlcomponents
    qmlRegisterType<MyItem>(uri, 1, 0, "CvCamView");
}

Q_EXPORT_PLUGIN2(CvCamView, CvCamViewPlugin)

//int main(int argc, char *argv[]){
//    QApplication* app = new QApplication(argc, argv);
//    MyItem* camView = new MyItem();
//    return app->exec();
//}
