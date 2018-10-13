cmake_minimum_required(VERSION 3.6)
project (vse)

add_subdirectory(al)
add_subdirectory(sb)

# This will set vse as the startup project for the *.sln solution
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sb)
