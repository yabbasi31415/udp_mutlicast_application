cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(UdpMulticast)

if(LOG_ACTIVE_LEVEL)
 set(LOG_TYPE ${LOG_ACTIVE_LEVEL} CACHE INTEGER "integer set")
endif()
configure_file(config.h.in config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} ${SOURCES})

set(APPLICATION application.cpp)

# Add executable target with source files listed in SOURCE_FILES variable

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.1 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    add_executable(multicast_app ${APPLICATION}) 
    target_link_libraries(multicast_app Boost::filesystem Boost::regex)
endif() 