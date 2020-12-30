cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(udp_receiver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB sources *.h 
                dialog.cpp 
                udp_receiver.cpp)

find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.1 COMPONENTS filesystem regex) 

add_executable(${PROJECT_NAME} ${sources}) 
target_link_libraries(${PROJECT_NAME} Boost::filesystem Boost::regex)
 

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

###########

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(udp_sender)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sources udp_sender_receiver.h 
                udp_sender.cpp)

find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.1 COMPONENTS filesystem regex) 

add_executable(${PROJECT_NAME} ${sources}) 
target_link_libraries(${PROJECT_NAME} Boost::filesystem Boost::regex)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()