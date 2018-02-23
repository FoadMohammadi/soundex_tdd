project(chapterFirstExample)
cmake_minimum_required(VERSION 2.8.2)

include_directories($ENV{GMOCK_HOME}/googlemock/include $ENV{GMOCK_HOME}/googletest/include)
link_directories($ENV{GMOCK_HOME}/googlemock/mybuild $ENV{GMOCK_HOME}/googletest/mybuild)
add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(sources 
   main.cpp 
   SoundexTest.cpp)
add_executable(test_soundex ${sources})
target_link_libraries(test_soundex gmock)
target_link_libraries(test_soundex gtest)
