cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(udp_multicast_example)

file(GLOB sources *.cpp *.h)
add_executable(${PROJECT_NAME} ${sources})

add_dependencies(${PROJECT_NAME} UdpMulticast)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} UdpMulticast)