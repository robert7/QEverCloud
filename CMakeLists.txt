cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/QEverCloud/cmake/modules")
include(QEverCloudCMakePolicies)
SET_POLICIES()

if("${CMAKE_MAJOR_VERSION}" GREATER "2")
  project(QEverCloud
          VERSION 3.0.0)
else()
  project(QEverCloud)
  set(PROJECT_VERSION_MAJOR "3")
  set(PROJECT_VERSION_MINOR "0")
  set(PROJECT_VERSION_PATCH "0")
  set(PROJECT_VERSION_COUNT 3)
  set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
endif()

set(PROJECT_VENDOR "Dmitry Ivanov")
set(PROJECT_COPYRIGHT_YEAR "2015-2016")
set(PROJECT_DOMAIN_FIRST "qevercloud")
set(PROJECT_DOMAIN_SECOND "com")
set(PROJECT_DOMAIN "${PROJECT_DOMAIN_FIRST}.${PROJECT_DOMAIN_SECOND}")

include(QEverCloudDoxygen)

set(BUILD_DOCUMENTATION ON CACHE BOOL "Build documentation for QEverCloud")
set(BUILD_QCH_DOCUMENTATION OFF CACHE BOOL "Build documentation for QEverCloud in qch format")

if(BUILD_DOCUMENTATION)
  # set Doxygen documentation properties
  set(DOXY_INPUT "${PROJECT_SOURCE_DIR}/QEverCloud/headers ${PROJECT_SOURCE_DIR}/README.md")
  set(DOXY_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
  set(DOXY_RECURSIVE "YES")
  set(DOXY_PROJECT_NAME ${PROJECT_NAME})
  set(DOXY_PROJECT_NUMBER "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
  set(DOXY_PROJECT_BRIEF "\"Unofficial Evernote Cloud API for Qt\"")
  set(DOXY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/doc")
  set(DOXY_WARN_IF_UNDOCUMENTED "NO")
  set(DOXY_EXTRACT_ALL "YES")
  if(BUILD_QCH_DOCUMENTATION)
    set(DOXY_GENERATE_QHP "YES")
  else()
    set(DOXY_GENERATE_QHP "NO")
  endif()
  ADD_DOCUMENTATION(doc Doxyfile)
endif()

include(QEverCloudCompilerSettings)
include(QEverCloudSetupQt)

if(USE_QT5)
  set(QEVERCLOUD_QT_VERSION_SUFFIX "-qt5")
else()
  set(QEVERCLOUD_QT_VERSION_SUFFIX "-qt4")
endif()

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/QEverCloud${QEVERCLOUD_QT_VERSION_SUFFIX})
endif()
set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/${DEF_INSTALL_CMAKE_DIR}" CACHE PATH "Installation directory for CMake files")

configure_file(QEverCloud/cmake/modules/QEverCloudBuildTreeSettings.cmake.in
  ${PROJECT_BINARY_DIR}/QEverCloud${QEVERCLOUD_QT_VERSION_SUFFIX}BuildTreeSettings.cmake @ONLY)
configure_file(QEverCloud/cmake/modules/QEverCloudConfig.cmake.in
  ${PROJECT_BINARY_DIR}/QEverCloud${QEVERCLOUD_QT_VERSION_SUFFIX}Config.cmake @ONLY)
configure_file(QEverCloud/cmake/modules/QEverCloudConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/QEverCloud${QEVERCLOUD_QT_VERSION_SUFFIX}ConfigVersion.cmake @ONLY)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_subdirectory(QEverCloud)

add_custom_target(check COMMAND "${CMAKE_CTEST_COMMAND}" "--verbose")
