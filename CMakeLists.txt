cmake_minimum_required(VERSION 3.15)
project(Ass1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Incude)

add_executable(Ass1
    Incude/Action.h
    Incude/json.h
    Incude/Session.h
    Incude/User.h
    Incude/Watchable.h
    src/Action.cpp
    src/main.cpp
    src/Session.cpp
    src/User.cpp
    src/Watchable.cpp)
