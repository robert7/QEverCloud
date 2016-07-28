cmake_minimum_required(VERSION 2.8.11)

include(QEverCloudCMakePolicies)
SET_POLICIES()

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

set(BUILD_SHARED ON CACHE BOOL "Build shared library, otherwise static library")

set(ALL_HEADERS_AND_SOURCES ${PUBLIC_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${NON_GENERATED_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${GENERATED_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${PRIVATE_HEADERS})
list(APPEND ALL_HEADERS_AND_SOURCES ${SOURCES})

set(WITH_QT_VERSION_SUFFIX ON CACHE BOOL "Add suffix denoting the major version of Qt to the library name")

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
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# install public headers
foreach(ITEM ${PUBLIC_HEADERS})
  install(FILES ${ITEM} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
endforeach()

foreach(ITEM ${NON_GENERATED_HEADERS})
  install(FILES ${ITEM} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/qevercloud)
endforeach()

foreach(ITEM ${GENERATED_HEADERS})
  install(FILES ${ITEM} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/qevercloud/generated)
endforeach()

# install cmake module
if(BUILD_SHARED AND WITH_QT_VERSION_SUFFIX)
  if(USE_QT5)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/FindLibQEverCloud-qt5.cmake DESTINATION ${INSTALL_CMAKE_DIR})
  else()
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/FindLibQEverCloud-qt4.cmake DESTINATION ${INSTALL_CMAKE_DIR})
  endif()
endif()
