cmake_minimum_required(VERSION 3.6)
project (vse)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(3rd_party)
find_package(OpenGL REQUIRED)

set(GLFW_ROOT_DIR "3rd_party/glfw")
if(WIN32)
	set(GLFW_USE_STATIC_LIBS "1")
endif()
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})

set (HEADERS)
set (SOURCES 
        "src/main.cpp"
        "src/vec2.cpp"
		"src/input.cpp"
		"src/window.cpp"
    )

add_executable(vse ${HEADERS} ${SOURCES})


if (MSVC)
    target_compile_options (vse PRIVATE /W4)
	target_link_libraries(vse glad ${GLFW_LIBRARIES})
else()
    target_compile_options (vse PRIVATE -Wall -Wextra -Wpedantic)
	target_link_libraries(vse glad glfw3 dl pthread X11 m)
endif()

target_include_directories (vse PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/vse)
target_include_directories (vse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# This will set vse as the startup project for the *.sln solution
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vse)
