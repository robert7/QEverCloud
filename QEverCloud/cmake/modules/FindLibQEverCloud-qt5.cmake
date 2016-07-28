# - Try to find LibQEverCloud-qt5
# Once done this will define
#  LibQEverCloud-qt5_FOUND - System has libQEverCloud-qt5
#  LIBQEVERCLOUD_QT5_INCLUDE_DIRS - The libQEverCloud-qt5 include directories
#  LIBQEVERCLOUD_QT5_LIBRARIES - The libraries needed to use libQEverCloud-qt5
#  LIBQEVERCLOUD_QT5_DEFINITIONS - The compiler switches for libQEverCloud-qt5

set(LIBQEVERCLOUD_ROOT
    "${LIBQEVERCLOUD_ROOT}"
    CACHE
    PATH
    "Root directory to look for QEverCloud-qt5 library and development headers in")

find_path(LIBQEVERCLOUD_QT5_INCLUDE_DIR
          NAMES
          QEverCloud.h
          PATHS
          "${LIBQEVERCLOUD_ROOT}"
          PATH_SUFFIXES
          include)

# Library
find_library(LIBQEVERCLOUD_QT5_LIBRARY
             NAMES
             libQEverCloud-qt5.so libQEverCloud-qt5.dylib libQEverCloud-qt5.dll
             PATHS
             "${LIBQEVERCLOUD_ROOT}"
             PATH_SUFFIXES
             lib)

# Dependencies:

macro(find_dependency DEPENDENCY)
  if(NOT ${DEPENDENCY}_FOUND)
    if(LibQEverCloud-qt5_FIND_REQUIRED)
      find_package(${DEPENDENCY} REQUIRED)
    else()
      find_package(${DEPENDENCY} QUIET)
      if(NOT ${DEPENDENCY}_FOUND)
        return()
      endif()
    endif()
  endif()
endmacro()

# 1) OpenSSL
find_dependency(OpenSSL)

# 2) Qt5 components
find_dependency(Qt5Core)
find_dependency(Qt5Network)
find_dependency(Qt5Widgets)

# Need special treatment for components responsible for OAuth as they may come in many flavours
# depending on Qt version
if(Qt5Core_VERSION VERSION_LESS "5.4.0")
  find_dependency(Qt5WebKit)
  find_dependency(Qt5WebKitWidgets)
elseif(Qt5Core_VERSION VERSION_LESS "5.6.0")
  find_dependency(Qt5WebEngine)
  find_dependency(Qt5WebEngineWidgets)
  set(LIBQEVERCLOUD_QT5_DEFINITIONS "-DQEVERCLOUD_USE_QT_WEB_ENGINE")
else()
  find_dependency(Qt5WebEngineCore)
  find_dependency(Qt5WebEngineWidgets)
  set(LIBQEVERCLOUD_QT5_DEFINITIONS "-DQEVERCLOUD_USE_QT_WEB_ENGINE")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibQEverCloud-qt5 DEFAULT_MSG
                                  LIBQEVERCLOUD_QT5_LIBRARY 
                                  LIBQEVERCLOUD_QT5_INCLUDE_DIR)

mark_as_advanced(LIBQEVERCLOUD_QT5_LIBRARY LIBQEVERCLOUD_QT5_INCLUDE_DIR)

set(LIBQEVERCLOUD_QT5_LIBRARIES ${LIBQEVERCLOUD_QT5_LIBRARY})
set(LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${LIBQEVERCLOUD_QT5_INCLUDE_DIR})
list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${OpenSSL_INCLUDE_DIRS})
list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5Core_INCLUDE_DIRS})
list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5Network_INCLUDE_DIRS})
list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5Widgets_INCLUDE_DIRS})

if(Qt5Core_VERSION VERSION_LESS "5.4.0")
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebKit_INCLUDE_DIRS})
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebKitWidgets_INCLUDE_DIRS})
elseif(Qt5Core_VERSION VERSION_LESS "5.6.0")
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebEngine_INCLUDE_DIRS})
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebEngineWidgets_INCLUDE_DIRS})
else()
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebEngineCore_INCLUDE_DIRS})
  list(APPEND LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${Qt5WebEngineWidgets_INCLUDE_DIRS})
endif()
