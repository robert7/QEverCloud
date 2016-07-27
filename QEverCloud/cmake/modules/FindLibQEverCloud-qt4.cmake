# - Try to find LibQEverCloud-qt4
# Once done this will define
#  LibQEverCloud-qt4_FOUND - System has libQEverCloud-qt4
#  LIBQEVERCLOUD_QT4_INCLUDE_DIRS - The libQEverCloud-qt4 include directories
#  LIBQEVERCLOUD_QT4_LIBRARIES - The libraries needed to use libQEverCloud-qt4

# Dependencies
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

# Include dir
find_path(LIBQEVERCLOUD_QT4_INCLUDE_DIR NAMES QEverCloud.h)

# Library
find_library(LIBQEVERCLOUD_QT4_LIBRARY NAMES libQEverCloud-qt4)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibQEverCloud-qt4 DEFAULT_MSG
                                  LIBQEVERCLOUD_QT4_LIBRARY 
                                  LIBQEVERCLOUD_QT4_INCLUDE_DIR)

mark_as_advanced(LIBQEVERCLOUD_QT4_LIBRARY LIBQEVERCLOUD_QT4_INCLUDE_DIR)

set(LIBQEVERCLOUD_QT4_LIBRARIES ${LIBQEVERCLOUD_QT4_LIBRARY})
set(LIBQEVERCLOUD_QT4_INCLUDE_DIRS ${LIBQEVERCLOUD_QT4_INCLUDE_DIR})
