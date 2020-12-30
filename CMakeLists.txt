cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(udp_multicast_application)

# SET CMAKE FLAGS FOR BUILD AND RELEASE

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -DNDEBUG -O3 -pthread")

message("-- Build Type: ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DFLAGS="RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
    message("-- Building with Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DFLAGS="DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    message("-- Building with Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

add_subdirectory(app)

## CMAKE MESSAGES
MESSAGE(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "CMAKE_CXX_FLAGS_RELEASE flags: " ${CMAKE_CXX_FLAGS_RELEASE})
