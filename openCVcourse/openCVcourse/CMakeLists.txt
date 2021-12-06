cmake_minimum_required(VERSION 3.5)

project(FourierTask_assignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV
find_package( OpenCV REQUIRED )

add_executable(FourierTask_assignment FourierTask_assignment.cpp)
target_link_libraries(FourierTask_assignment PRIVATE ${OpenCV_LIBS})
