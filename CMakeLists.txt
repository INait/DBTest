cmake_minimum_required(VERSION 3.10)

# set the project name
project(DBTestProject)

file(GLOB SOURCES 
	"src/*.cpp"
	"src/*.h"
)

# add the executable
add_executable(DBTestProject ${SOURCES})
