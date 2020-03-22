cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(chat)

# file(GLOB sources *.cpp *.h)
file(GLOB sources parser_example.cpp)
add_executable(${PROJECT_NAME} ${sources})

add_dependencies(${PROJECT_NAME} UdpMulticast)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNALS_SOURCE_DIR}/Lyra/include)

target_link_libraries(${PROJECT_NAME} UdpMulticast)