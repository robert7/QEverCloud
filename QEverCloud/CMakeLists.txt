cmake_minimum_required(VERSION 2.8.11)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

include(QEverCloudAdditionalCompilerWarnings)

set(PUBLIC_HEADERS
    headers/QEverCloud.h
    headers/QEverCloudOAuth.h)

set(NON_GENERATED_HEADERS
    headers/qevercloud/export.h
    headers/qevercloud/oauth.h
    headers/qevercloud/exceptions.h
    headers/qevercloud/globals.h
    headers/qevercloud/thumbnail.h
    headers/qevercloud/AsyncResult.h
    headers/qevercloud/Optional.h
    headers/qevercloud/EverCloudException.h
    headers/qevercloud/qt4helpers.h
    headers/qevercloud/EventLoopFinisher.h)

set(GENERATED_HEADERS
    headers/qevercloud/generated/constants.h
    headers/qevercloud/generated/services.h
    headers/qevercloud/generated/types.h
    headers/qevercloud/generated/EDAMErrorCode.h)

set(PRIVATE_HEADERS
    src/thrift.h
    src/http.h
    src/impl.h
    src/generated/types_impl.h)

set(SOURCES
    src/exceptions.cpp
    src/oauth.cpp
    src/http.cpp
    src/services_nongenerated.cpp
    src/AsyncResult.cpp
    src/EverCloudException.cpp
    src/EventLoopFinisher.cpp
    src/thumbnail.cpp
    src/generated/constants.cpp
    src/generated/services.cpp
    src/generated/types.cpp)

option(BUILD_SHARED "Build shared library, otherwise static library" ON)

set(ALL_HEADERS_AND_SOURCES ${PUBLIC_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${NON_GENERATED_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${GENERATED_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${PRIVATE_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${SOURCES})

option(WITH_QT_VERSION_SUFFIX "Add suffix denoting the major version of Qt to the library name" ON)

if(WITH_QT_VERSION_SUFFIX)
  if(USE_QT5)
    set(LIBNAME_SUFFIX "-qt5")
  else()
    set(LIBNAME_SUFFIX "-qt4")
  endif()
else()
  set(LIBNAME_SUFFIX "")
endif()

if(MSVC)
  set(LIBNAME "lib${PROJECT_NAME}${LIBNAME_SUFFIX}")
else()
  set(LIBNAME ${PROJECT_NAME}${LIBNAME_SUFFIX})
endif()

if(BUILD_SHARED)
  add_definitions("-DQEVERCLOUD_SHARED_LIBRARY")
  add_library(${LIBNAME} SHARED ${ALL_HEADERS_AND_SOURCES})
else()
  add_definitions("-DQEVERCLOUD_STATIC_LIBRARY")
  add_library(${LIBNAME} STATIC ${ALL_HEADERS_AND_SOURCES})
endif()

target_link_libraries(${LIBNAME} ${QT_LIBRARIES} ${OPENSSL_LIBRARIES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

# install shared library
install(TARGETS ${LIBNAME}
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  RUNTIME DESTINATION ${INSTALL_BIN_DIR})

# install public headers
foreach(ITEM ${PUBLIC_HEADERS})
  install(FILES ${ITEM} DESTINATION ${INSTALL_INCLUDE_DIR})
endforeach()

foreach(ITEM ${NON_GENERATED_HEADERS})
  install(FILES ${ITEM} DESTINATION ${INSTALL_INCLUDE_DIR}/qevercloud)
endforeach()

foreach(ITEM ${GENERATED_HEADERS})
  install(FILES ${ITEM} DESTINATION ${INSTALL_INCLUDE_DIR}/qevercloud/generated)
endforeach()

# install cmake module
if(USE_QT5)
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/FindLibQEverCloud-qt5.cmake DESTINATION ${INSTALL_CMAKE_DIR})
else()
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/FindLibQEverCloud-qt4.cmake DESTINATION ${INSTALL_CMAKE_DIR})
endif()
