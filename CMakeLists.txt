cmake_minimum_required(VERSION 3.10)

project(LightWebServer)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(server
    src/main.cpp
    src/server/HttpServer.cpp
    src/http/HttpConn.cpp
)
