#include "cvcamview_plugin.h"
#include "myitem.h"

#include <QtDeclarative/qdeclarative.h>

void CvCamViewPlugin::registerTypes(const char *uri)
{
    // @uri com.ferrazz.qmlcomponents
    qmlRegisterType<MyItem>(uri, 1, 0, "MyItem");
}

Q_EXPORT_PLUGIN2(CvCamView, CvCamViewPlugin)

