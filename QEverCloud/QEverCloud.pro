TARGET = QEverCloud

win32 {
    TARGET = lib$$qtLibraryTarget($$TARGET)
}
else {
    TARGET = $$qtLibraryTarget($$TARGET)
}

TEMPLATE = lib

build_shared {
    CONFIG += dll
    win32-msvc* {
        LIBS += Advapi32.lib Setupapi.lib
        CONFIG -= dll
        CONFIG += shared static
        QMAKE_LFLAGS += /IMPLIB:$${TARGET}.lib
    }
}
else {
    CONFIG += staticlib
}

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
    headers/QEverCloudOAuth.h

NON_GENERATED_PUBLIC_HEADERS += \
    headers/qevercloud/export.h \
    headers/qevercloud/oauth.h \
    headers/qevercloud/exceptions.h \
    headers/qevercloud/globals.h \
    headers/qevercloud/thumbnail.h \
    headers/qevercloud/AsyncResult.h \
    headers/qevercloud/Optional.h \
    headers/qevercloud/EverCloudException.h \
    headers/qevercloud/qt4helpers.h \
    headers/qevercloud/EventLoopFinisher.h

GENERATED_PUBLIC_HEADERS += \
    headers/qevercloud/generated/constants.h \
    headers/qevercloud/generated/services.h \
    headers/qevercloud/generated/types.h \
    headers/qevercloud/generated/EDAMErrorCode.h

PRIVATE_HEADERS += \
    src/thrift.h \
    src/http.h \
    src/impl.h \
    src/generated/types_impl.h

HEADERS += $$PUBLIC_HEADERS $$NON_GENERATED_PUBLIC_HEADERS $$GENERATED_PUBLIC_HEADERS
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

isEmpty(PREFIX) {
    PREFIX = /usr/local
}

win32 {
    staticlib.path += $$PREFIX/lib
    staticlib.files += $$OUT_PWD/$$DESTDIR/$${TARGET}.lib

    sharedlib.path += $$PREFIX/bin
    sharedlib.files += $$OUT_PWD/$$DESTDIR/$${TARGET}.dll

    message("The TARGET variable is: ")
    message($$TARGET)
    message("Wrapped into qtLibraryTarget: ")
    message($$qtLibraryTarget($$TARGET))
    message("The OUT_PWD variable is: ")
    message($$OUT_PWD)
    message("The overall static lib path: ")
    message($$OUT_PWD/$$DESTDIR/$${TARGET}.lib)
    message("The overall shared lib path: ")
    message($$OUT_PWD/$$DESTDIR/$${TARGET}.dll)
}
else {
    target.path += $$PREFIX/lib
}

message("staticlib.files = ")
message($${staticlib.files})
message("sharedlib.files = ")
message($${sharedlib.files})

public_headers.path = $$PREFIX/include
public_headers.files = $$PUBLIC_HEADERS

non_generated_public_headers.path = $$PREFIX/include/qevercloud
non_generated_public_headers.files = $$NON_GENERATED_PUBLIC_HEADERS

generated_public_headers.path = $$PREFIX/include/qevercloud/generated
generated_public_headers.files = $$GENERATED_PUBLIC_HEADERS

INSTALLS = public_headers non_generated_public_headers generated_public_headers
win32 {
    INSTALLS += sharedlib
    INSTALLS += staticlib
}
else {
    INSTALLS += target
}

