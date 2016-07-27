# - Try to find LibQEverCloud-qt5
# Once done this will define
#  LibQEverCloud-qt5_FOUND - System has libQEverCloud-qt5
#  LIBQEVERCLOUD_QT5_INCLUDE_DIRS - The libQEverCloud-qt5 include directories
#  LIBQEVERCLOUD_QT5_LIBRARIES - The libraries needed to use libQEverCloud-qt5

# Dependencies
if(NOT OpenSSL_FOUND)
  if(LibQEverCloud-qt5_FIND_REQUIRED)
    find_package(OpenSSL REQUIRED)
  else()
    find_package(OpenSSL QUIET)
    if(NOT OpenSSL_FOUND)
      return()
    endif()
  endif()
endif()

# Include dir
find_path(LIBQEVERCLOUD_QT5_INCLUDE_DIR NAMES QEverCloud.h)

# Library
find_library(LIBQEVERCLOUD_QT5_LIBRARY NAMES libQEverCloud-qt5)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibQEverCloud-qt5 DEFAULT_MSG
                                  LIBQEVERCLOUD_QT5_LIBRARY 
                                  LIBQEVERCLOUD_QT5_INCLUDE_DIR)

mark_as_advanced(LIBQEVERCLOUD_QT5_LIBRARY LIBQEVERCLOUD_QT5_INCLUDE_DIR)

set(LIBQEVERCLOUD_QT5_LIBRARIES ${LIBQEVERCLOUD_QT5_LIBRARY})
set(LIBQEVERCLOUD_QT5_INCLUDE_DIRS ${LIBQEVERCLOUD_QT5_INCLUDE_DIR})
