cmake_minimum_required(VERSION 3.6)
project (al)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(3rd_party)
find_package(OpenGL REQUIRED)

set(GLFW_ROOT_DIR "3rd_party/glfw")
if(WIN32)
	set(GLFW_USE_STATIC_LIBS "1")
endif()
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "src/" "*.cpp") 
file(GLOB_RECURSE HEADERS "src/" "*.hpp") 
file(GLOB PUBLIC_HEADERS "include/${PROJECT_NAME}/*.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})

target_include_directories (${PROJECT_NAME} PRIVATE
    include/${PROJECT_NAME}/math
    include/${PROJECT_NAME}/gl
    include/${PROJECT_NAME}/ecs
)
target_include_directories (${PROJECT_NAME} PUBLIC
    include/
    3rd_party/
    3rd_party/glfw/include/
)
set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS} ${PUBLIC_HEADERS})

if (MSVC)
    target_compile_options (${PROJECT_NAME} PRIVATE /W4)
	target_link_libraries(${PROJECT_NAME} glad ${GLFW_LIBRARIES})
else()
    target_compile_options (${PROJECT_NAME} PRIVATE -std=c++14 -Wall -Wextra -Wpedantic -Wfatal-errors)
	target_link_libraries(${PROJECT_NAME} glad glfw3 dl pthread X11 m)
endif()


