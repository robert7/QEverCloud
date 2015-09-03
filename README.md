QEverCloud
==========

**Unofficial Evernote Cloud API for Qt**

## What's this

This library presents complete Evernote SDK for Qt. 
All the functionality that is described on [Evernote site](http://dev.evernote.com/doc/)
is implemented and ready to use. In particular OAuth authentication is implemented.

Read doxygen generated [documentation](http://d1vanov.github.io/QEverCloud) for detailed info.

The documentation is also available as a .qch file which you can register with
your copy of Qt Creator to have context-sensitive help. See *qch* subdir.


## Compatibility

The library supports both Qt4 and Qt5 branches. 

### QtWebKit vs QWebEngine
The library uses Qt's web facilities for OAuth authentication. These can be based on either QtWebKit (for Qt4 and older versions of Qt5) or QWebEngine (for more recent versions of Qt5). By default QtWebKit is used but that can be altered via qmake option CONFIG+=use_qwebengine. 

### C++11 features
These are not used directly but only through macros like Q_DECL_OVERRIDE, Q_STATIC_ASSERT_X, QStringLiteral and others + these macros are also backported to Qt4 version of the library. So the library should be usable even with not C++11-compliant compiler. 

The original version of the library was developer and tested primarily on Windows, I personally only have access to Windows machines from time to time and focus primarily on Linux support. 

## How to compile

QEverCloud depends on Qt only. So there is nothing special to compiling it. Only the decision whether to use QtWebKit or QWebEngine for OAuth needs to be done before building the library (see the note above).

## How to link

* Link compiled library to your project in the usual way. 
* Add it's *include* subdir to your app INCLUDEPATH qmake variable.
* Add to QT variabe the *network* module. If you use OAuth functionality than add also *widgets* and *webkitwidgets* modules.

Include *QEverCloud.h* or *QEverCloudOAuth.h* to use the library. The latter header is needed if you use OAuth functionality.

## Runtime dependencies

Qt uses OpenSSL to implement https protocol. As a result your app using the library needs to be linked to OpenSSL dynamically linked libraries (libeay32 and ssleay32). On Windows these must be availabe in the PATH variable. 
