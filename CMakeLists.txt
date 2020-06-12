cmake_minimum_required(VERSION 2.8)

project(C3TL)

# version
set(C3TL_VERSION_MAJOR 0)
set(C3TL_VERSION_MINOR 9)
set(C3TL_VERSION_PATCH 0)
set(C3TL_VERSION "${C3TL_VERSION_MAJOR}.${C3TL_VERSION_MINOR}.${C3TL_VERSION_PATCH}")
message(STATUS "The version of this project is: ${C3TL_VERSION_VERSION}")

include_directories(${PROJECT_SOURCE_DIR}/include)

# build type
set(CMAKE_BUILD_TYPE debug)
message(STATUS "The build type is: ${CMAKE_BUILD_TYPE}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-array-bounds")
        # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)
    endif()
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
        message(FATAL_ERROR "required GCC 5.0 or later")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if("${CMAKE_BUILD_TYPE}" STREQUAL "release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare")
        # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
    endif()
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
        message(FATAL_ERROR "required Clang 3.5 or later")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
