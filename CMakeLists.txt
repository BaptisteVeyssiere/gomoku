cmake_minimum_required(VERSION 2.6)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

include_directories(include)

add_executable(pbrain-GodzIA ${SOURCES} ${HEADERS})
