QEverCloud
==========

**Unofficial Evernote Cloud API for Qt**

## What's this

This library presents the complete Evernote SDK for Qt.
All the functionality that is described on [Evernote site](http://dev.evernote.com/doc/)
is implemented and ready to use. In particular OAuth authentication is implemented.

Read doxygen generated [documentation](http://d1vanov.github.io/QEverCloud) for detailed info.

The documentation can also be generated in the form of a .qch file which you can register with
your copy of Qt Creator to have context-sensitive help. See below for more details.

## How to build

The project can be built and shipped as either static library or shared library. Dll export/import symbols necessary for Windows platform are supported.

Dependencies:
1. Qt components:
   * For Qt4: QtCore, QtGui, QtNetwork, QtWebKit, QtTest
   * For Qt5: Qt5Core, Qt5Widgets, Qt5Network, Qt5Test and either:
     * Qt5WebKit and Qt5WebKitWidgets - for Qt < 5.4
     * Qt5WebEngine and Qt5WebEngineWidgets - for Qt < 5.6
     * Qt5WebEngineCore and Qt5WebEngineWidgets - for Qt >= 5.6
2. OpenSSL

The project uses CMake build system which can be used as simply as follows (on Unix platforms):
```
mkdir build
cd build
cmake ../
make
```

That would build the shared library based on Qt version you have installed and available within your environment variables. In order to build and install the library in some particular prefix one can do the following:
```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<...> ../
make
make install
```

More CMake configurations options available:

*BUILD_DOCUMENTATION* - when *ON*, attempts to find Doxygen and in case of success adds *doc* target so the documentation can be built using `make doc` command after the `cmake ../` step. By default this option is on.

*BUILD_QCH_DOCUMENTATION* - when *ON*, passes instructions on to Doxygen to build the documentation in *qch* format. This option only has any meaning if *BUILD_DOCUMENTATION* option is on. By default this option is off.

*BUILD_SHARED* - when *ON*, CMake configures the build for the shared library. By default this option is on.

*WITH_QT_VERSION_SUFFIX* - when *ON*, the "-qt4" or "-qt5" suffix is being added to the name of the built library file. That way one could have both Qt4 and Qt5 versions of the library installed on the same machine simultaneously. By default this option is on.

If both *BUILD_SHARED* and *WITH_QT_VERSION_SUFFIX* options are *ON*, `make install` would install the CMake module necessary for applications using CMake's `find_package` command to find the installation of the library.

## Compatibility

The previous versions the library used **qmake** build system and only allowed building as a static library. The latest version of the library uses **CMake** build system which allows building either shared or static library. For compatibility the project file for qmake build system was left within the project's source tree, however, it still only allows to build a static library. Plus, the deprecation warning is displayed when one tries to use the project file for qmake build system.

The library can be built with both Qt4 and Qt5 versions of the framework. There are several details dependent on the version of the framework though.

### QtWebKit vs QWebEngine

The library uses Qt's web facilities for OAuth authentication. These can be based on either QtWebKit (for Qt4 and older versions of Qt5) or QWebEngine (for more recent versions of Qt5). With CMake build system the choice happens automatically during the pre-build configuration based on the used version of Qt. With qmake build system QtWebKit is used by default but that can be altered via qmake option `CONFIG+=use_qwebengine`.

### C++11/14/17 features

The library does not use any C++11/14/17 features directly but only through macros like `Q_DECL_OVERRIDE`, `Q_STATIC_ASSERT_X`, `QStringLiteral` and others. Some of these macros are also "backported" to Qt4 version of the library i.e. they are defined by the library itself for Qt4 version. So the library should be buildable even with not C++11/14/17-compliant compiler.

## Include files for applications using the library

Include *QEverCloud.h* or *QEverCloudOAuth.h* into the application's source files. The latter header is needed if you use OAuth functionality.
