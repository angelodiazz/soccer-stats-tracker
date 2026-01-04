cmake_minimum_required(VERSION 4.1)
project(soccer_stats_tracker)

set(CMAKE_CXX_STANDARD 17)

add_executable(soccer_stats_tracker
        src/main.cpp
        src/Input.cpp
        src/Player.cpp
        src/StatsTracker.cpp
)

target_include_directories(soccer_stats_tracker PRIVATE src)
