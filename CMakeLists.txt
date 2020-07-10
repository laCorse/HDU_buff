cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(HDU_Buff)


set(INC_DIRS Inc)


include_directories(${INC_DIRS})
link_libraries(${LIB_DIRS})

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(HDU_Buff main.cpp Inc/Buff.h Src/Buff.cpp)

target_link_libraries(HDU_Buff ${LIB_DIRS})


target_link_libraries(HDU_Buff ${OpenCV_LIBS})
target_link_libraries(HDU_Buff Threads::Threads)
