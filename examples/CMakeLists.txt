cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(chat)

# file(GLOB sources *.cpp *.h)
file(GLOB sources command_line_parser_example.cpp)
# add_executable(${PROJECT_NAME} ${sources})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.65.1 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    add_executable(${PROJECT_NAME} ${sources}) 
    target_link_libraries(${PROJECT_NAME} Boost::filesystem Boost::regex)
endif() 


add_dependencies(${PROJECT_NAME} UdpMulticast)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNALS_SOURCE_DIR}/Lyra/include)

target_link_libraries(${PROJECT_NAME} UdpMulticast)