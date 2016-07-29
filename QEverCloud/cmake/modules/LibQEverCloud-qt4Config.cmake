# - Try to find LibQEverCloud-qt4
# Once done this will define
#  LibQEverCloud-qt4_FOUND - System has libQEverCloud-qt4
#  LIBQEVERCLOUD_QT4_INCLUDE_DIRS - The libQEverCloud-qt4 include directories
#  LIBQEVERCLOUD_QT4_LIBRARIES - The libraries needed to use libQEverCloud-qt4

set(LIBQEVERCLOUD_ROOT
    "${LIBQEVERCLOUD_ROOT}"
    CACHE
    PATH
    "Root directory to look for QEverCloud-qt5 library and development headers in")

find_path(LIBQEVERCLOUD_QT4_INCLUDE_DIR
          NAMES
          QEverCloud.h
          PATHS
          "${LIBQEVERCLOUD_ROOT}"
          PATH_SUFFIXES
          include)

# Library
set(CMAKE_FIND_LIBRARY_PREFIXES lib)
set(CMAKE_FIND_LIBRARY_SUFFIXES .dll .so .dylib)
find_library(LIBQEVERCLOUD_QT4_LIBRARY
             NAMES
             QEverCloud-qt4
             PATHS
             "${LIBQEVERCLOUD_ROOT}"
             PATH_SUFFIXES
             lib bin
             NO_DEFAULT_PATH)

# Dependencies:

# 1) OpenSSL
if(NOT OpenSSL_FOUND)
  if(LibQEverCloud-qt4_FIND_REQUIRED)
    find_package(OpenSSL REQUIRED)
  else()
    find_package(OpenSSL QUIET)
    if(NOT OpenSSL_FOUND)
      return()
    endif()
  endif()
endif()

# 2) Qt4
# Can't really determine whether all the required modules are already found, hence finding ourselves
if(LibQEverCloud-qt4_FIND_REQUIRED)
  find_package(Qt4 COMPONENTS QTCORE QTGUI QTNETWORK QTWEBKIT REQUIRED)
else()
  find_package(Qt4 COMPONENTS QTCORE QTGUI QTNETWORK QTWEBKIT QUIET)
  if(NOT Qt4_FOUND)
    return()
  endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibQEverCloud-qt4 DEFAULT_MSG
                                  LIBQEVERCLOUD_QT4_LIBRARY 
                                  LIBQEVERCLOUD_QT4_INCLUDE_DIR)

mark_as_advanced(LIBQEVERCLOUD_QT4_LIBRARY LIBQEVERCLOUD_QT4_INCLUDE_DIR)

set(LIBQEVERCLOUD_QT4_LIBRARIES ${LIBQEVERCLOUD_QT4_LIBRARY})
set(LIBQEVERCLOUD_QT4_INCLUDE_DIRS ${LIBQEVERCLOUD_QT4_INCLUDE_DIR})
list(APPEND LIBQEVERCLOUD_QT4_INCLUDE_DIRS ${OpenSSL_INCLUDE_DIRS})
list(APPEND LIBQEVERCLOUD_QT4_INCLUDE_DIRS ${QT_INCLUDES})
