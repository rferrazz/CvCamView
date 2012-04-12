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
    cvcamresolution.cpp \
    cvhaardetector.cpp

HEADERS += \
    cvcamview_plugin.h \
    cvcamview.h \
    cvcamresolution.h \
    cvhaardetector.h

OTHER_FILES = qmldir \
    COPYING \
    README.md \
    haarcascades/haarcascade_upperbody.xml \
    haarcascades/haarcascade_righteye_2splits.xml \
    haarcascades/haarcascade_profileface.xml \
    haarcascades/haarcascade_mcs_upperbody.xml \
    haarcascades/haarcascade_mcs_righteye.xml \
    haarcascades/haarcascade_mcs_rightear.xml \
    haarcascades/haarcascade_mcs_nose.xml \
    haarcascades/haarcascade_mcs_mouth.xml \
    haarcascades/haarcascade_mcs_lefteye.xml \
    haarcascades/haarcascade_mcs_leftear.xml \
    haarcascades/haarcascade_mcs_eyepair_small.xml \
    haarcascades/haarcascade_mcs_eyepair_big.xml \
    haarcascades/haarcascade_lowerbody.xml \
    haarcascades/haarcascade_lefteye_2splits.xml \
    haarcascades/haarcascade_fullbody.xml \
    haarcascades/haarcascade_frontalface_default.xml \
    haarcascades/haarcascade_frontalface_alt_tree.xml \
    haarcascades/haarcascade_frontalface_alt2.xml \
    haarcascades/haarcascade_frontalface_alt.xml \
    haarcascades/haarcascade_eye_tree_eyeglasses.xml \
    haarcascades/haarcascade_eye.xml

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

RESOURCES +=
