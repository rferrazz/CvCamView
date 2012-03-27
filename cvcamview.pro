TEMPLATE = lib
TARGET = CvCamView
QT += declarative
CONFIG += qt plugin

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

TARGET = $$qtLibraryTarget($$TARGET)
uri = opencv.components

# Input
SOURCES += \
    cvcamview_plugin.cpp \
    cvcamview.cpp \
    cvcamresolution.cpp

HEADERS += \
    cvcamview_plugin.h \
    cvcamview.h \
    cvcamresolution.h

OTHER_FILES = qmldir \
    COPYING \
    README.md

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
symbian {
    TARGET.EPOCALLOWDLLDATA = 1
} else:unix {
    maemo5 | !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = /usr/lib/qt4/imports/$$replace(uri, \\., /)
    } else {
        installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
    }
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
