cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(QEverCloud)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QEverCloud/cmake/modules)

include(QEverCloudCompilerSettings)
include(QEverCloudSetupQt)
include(QEverCloudFindOpenSSL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

add_subdirectory(QEverCloud)

add_custom_target(check COMMAND "${CMAKE_CTEST_COMMAND}" "--verbose")
