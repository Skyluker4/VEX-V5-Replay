cmake_minimum_required (VERSION 3.12)

project (Interpreter)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall")
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(interpret src/main.cpp)
