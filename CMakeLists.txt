cmake_minimum_required(VERSION 3.10)

set(CMAKE_SYSTEM_VERSION "10.0.18362.0" CACHE STRING INTERNAL FORCE)
set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION "10.0.18362.0" CACHE STRING INTERNAL FORCE)

# set the project name
project(DBTestProject)

file(GLOB SOURCES 
	"src/*.cpp"
	"src/*.h"
	"src/network/*.cpp"
	"src/network/*.h"
)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)
find_package(Boost "1.74.0" COMPONENTS system date_time regex REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# add the executable
add_executable(DBTestProject ${SOURCES})
target_link_libraries(DBTestProject ${Boost_LIBRARIES})
