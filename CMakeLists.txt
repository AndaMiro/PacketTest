cmake_minimum_required(VERSION 3.16)
project(mirinae LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
	src/mirinae/Mirinae.cpp
	src/mirinae/core/Server.cpp
	src/mirinae/network/UdpNetwork.cpp
)

add_executable(mirinae ${SOURCES})

target_include_directories(mirinae PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)
target_link_libraries(mirinae PRIVATE Threads::Threads)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

