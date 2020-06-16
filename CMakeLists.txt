cmake_minimum_required(VERSION 2.6)

project(C3TL)

# version
set(C3TL_VERSION_MAJOR 1)
set(C3TL_VERSION_MINOR 0)
set(C3TL_VERSION_PATCH 1)
set(C3TL_VERSION "${C3TL_VERSION_MAJOR}.${C3TL_VERSION_MINOR}.${C3TL_VERSION_PATCH}")
message(STATUS "The version of this project is: ${C3TL_VERSION}")

include_directories(${PROJECT_SOURCE_DIR}/include)

option(ENABLE_DEBUG "Enable debug build" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# build type
if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE debug)
else()
    set(CMAKE_BUILD_TYPE release)
endif()
message(STATUS "The build type is: ${CMAKE_BUILD_TYPE}")

# codecov
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
message(STATUS "Enable code coverage: " ${ENABLE_COVERAGE})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.1")
        message(FATAL_ERROR "required GCC 4.8.1 or later")
    else()
        if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-array-bounds")
            # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)
        endif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.3.0")
        message(FATAL_ERROR "required Clang 3.3 or later")
    else()
        if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare")
            # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
        endif()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

# aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/test TEST_SOURCE_FILES)

# add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(${PROJECT_NAME}-test ${TEST_SOURCE_FILES})

