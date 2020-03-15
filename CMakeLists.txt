cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(udp_multicast_application)

# Add clang-format target if tool is available.
find_program(CLANG_FORMAT clang-format)
if (CLANG_FORMAT)
  message(STATUS "Found clang-format")
  configure_file("${PROJECT_SOURCE_DIR}/clang-format.sh.in"
    "${CMAKE_BINARY_DIR}/clang-format.sh" @ONLY)
  add_custom_target(clang-format COMMAND bash "${CMAKE_BINARY_DIR}/clang-format.sh")
endif()

# SET CMAKE FLAGS FOR BUILD AND RELEASE

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# set (CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} \
#   -fPIC -Wall -pedantic -Wextra -Werror \
#   -Wno-missing-braces -Wno-unused-variable \
#   -Wno-ignored-qualifiers  -fdiagnostics-color")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -DNDEBUG -O3")

message("-- Build Type: ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DFLAGS="RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
    message("-- Building with Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DFLAGS="DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
    message("-- Building with Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
endif()

# SET HEADER AND SOURCE FILE DIRECTORIES

set(EXTERNALS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/externals")

file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# OPTIONS TO ENABLE TESTS, BENCHMARKS AND EXAMPLES

add_subdirectory(src)

option(BUILD_EXAMPLES "Enable building examples" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(BUILD_BENCHMARKS "Enable building benchmarks" ON)
if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

option(BUILD_TESTS "Enable building tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()


## CMAKE MESSAGES
MESSAGE(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "CMAKE_CXX_FLAGS_RELEASE flags: " ${CMAKE_CXX_FLAGS_RELEASE})
if(ENABLE_LOGGING)
MESSAGE(STATUS "ENABLE_LOGGING: ON")
else()
    MESSAGE(STATUS "ENABLE_LOGGING: OFF")
endif()
