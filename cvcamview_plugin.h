#ifndef CVCAMVIEW_PLUGIN_H
#define CVCAMVIEW_PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class CvCamViewPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
    
public:
    void registerTypes(const char *uri);
};

#endif // CVCAMVIEW_PLUGIN_H

