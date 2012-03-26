#include "myitem.h"

#include <QtDeclarative/qdeclarative.h>

MyItem::MyItem(QDeclarativeItem *parent):
    QDeclarativeItem(parent), camera(0)
{
    setFlag(ItemHasNoContents, false);
    camThread = new camThread(camera);
}

MyItem::~MyItem()
{
}

