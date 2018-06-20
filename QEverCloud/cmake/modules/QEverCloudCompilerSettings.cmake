if(CMAKE_COMPILER_IS_GNUCXX)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  message(STATUS "Using GNU C++ compiler, version ${GCC_VERSION}")
  if(GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
    message(STATUS "This version of GNU C++ compiler supports C++11 standard.")
    set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
    add_definitions("-DCPP11_COMPLIANT=1")
    if(GCC_VERSION VERSION_GREATER 8.0 OR GCC_VERSION VERSION_EQUAL 8.0)
      if(GCC_VERSION VERSION_LESS 8.2)
        # NOTE: workaround for a problem similar to https://issues.apache.org/jira/browse/THRIFT-4584
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-tree-vrp -fno-inline -fno-tree-fre")
        set(CMAKE_C_FLAGS_RELEASE "-g -O0")
        set(CMAKE_CXX_FLAGS_RELEASE "-g -O0")
        set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O0")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O0")
      endif()
    endif()
  elseif(NOT GCC_VERSION VERSION_LESS 4.4)
    set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
  endif()
  if(BUILD_SHARED)
    set(CMAKE_CXX_FLAGS "-fvisibility=hidden ${CMAKE_CXX_FLAGS}")
  endif()
  if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "-fPIC -rdynamic ${CMAKE_CXX_FLAGS}")
  endif()
  if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(CMAKE_CXX_FLAGS "-ldl ${CMAKE_CXX_FLAGS}")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  execute_process(COMMAND ${CMAKE_C_COMPILER} --version OUTPUT_VARIABLE CLANG_VERSION)
  message(STATUS "Using LLVM/Clang C++ compiler, version info: ${CLANG_VERSION}")
  if(NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.1)
    message(STATUS "Your compiler supports C++11 standard.")
    add_definitions("-DCPP11_COMPLIANT=1")
  else()
    message(WARNING "Your compiler may not support all the necessary C++11 standard features
                     to build this project. If you'd get any compilation errors, consider
                     upgrading to a compiler version which fully supports the C++11 standard.")
  endif()
  set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC ${CMAKE_CXX_FLAGS}")
  if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" OR USE_LIBCPP)
    find_library(LIBCPP NAMES libc++.so libc++.so.1.0 libc++.dylib OPTIONAL)
    if(LIBCPP)
      message(STATUS "Using native Clang's C++ standard library: ${LIBCPP}")
      set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
      add_definitions("-DHAVELIBCPP")
    endif()
  endif()
elseif(MSVC)
  if(MSVC10)
    message(STATUS "Using VC++ 2010 compiler")
  elseif(MSVC11)
    message(STATUS "Using VC++ 2012 compiler")
  elseif(MSVC12)
    message(STATUS "Using VC++ 2013 compiler")
  elseif(MSVC14)
    message(STATUS "Using VC++ 2015 compiler")
  else()
    message(STATUS "Using unidentified version of VC++ compiler")
  endif()
  set(CMAKE_CXX_FLAGS "-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS ${CMAKE_CXX_FLAGS}")
endif()
