TARGET = QEverCloud
TEMPLATE = lib
CONFIG += staticlib

QT += network widgets

use_qwebengine {
QT += webenginewidgets webengine
DEFINES += USE_QT_WEB_ENGINE
}
else {
QT += webkitwidgets webkit
}

CONFIG += silent
CONFIG -= debug_and_release debug_and_release_target

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc

INCLUDEPATH += headers

PUBLIC_HEADERS += \
    headers/QEverCloud.h \
    headers/QEverCloudOAuth.h \
    headers/qevercloud/export.h \
    headers/qevercloud/oauth.h \
    headers/qevercloud/exceptions.h \
    headers/qevercloud/globals.h \
    headers/qevercloud/thumbnail.h \
    headers/qevercloud/AsyncResult.h \
    headers/qevercloud/Optional.h \
    headers/qevercloud/EverCloudException.h \
    headers/qevercloud/qt4helpers.h \
    headers/qevercloud/EventLoopFinisher.h \
    headers/qevercloud/generated/constants.h \
    headers/qevercloud/generated/services.h \
    headers/qevercloud/generated/types.h \
    headers/qevercloud/generated/EDAMErrorCode.h

PRIVATE_HEADERS += \
    src/thrift.h \
    src/http.h \
    src/impl.h \
    src/generated/types_impl.h

HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS

SOURCES += \
    src/exceptions.cpp \
    src/oauth.cpp \
    src/http.cpp \
    src/services_nongenerated.cpp \
    src/AsyncResult.cpp \
    src/EverCloudException.cpp \
    src/EventLoopFinisher.cpp \
    src/thumbnail.cpp \
    src/generated/constants.cpp \
    src/generated/services.cpp \
    src/generated/types.cpp
