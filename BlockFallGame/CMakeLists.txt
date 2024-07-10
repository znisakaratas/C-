cmake_minimum_required(VERSION 3.26)
project(assignment2)

set(CMAKE_CXX_STANDARD 11)

add_executable(assignment2 main.cpp
        BlockFall.h
        Leaderboard.h
        Leaderboard.h
        BlockFall.cpp
        Leaderboard.cpp
        LeaderboardEntry.cpp
        LeaderboardEntry.h
        Block.h
        GameController.cpp
        GameController.h)
