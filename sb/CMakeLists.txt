cmake_minimum_required(VERSION 3.6)
project (sb)

set (SOURCES
  "src/main.cpp"
)
file (GLOB SHADERS "shaders/*")

add_executable(${PROJECT_NAME} ${SOURCES} ${SHADERS})
target_link_libraries(${PROJECT_NAME} al)

if (MSVC)
    target_compile_options (${PROJECT_NAME}  PRIVATE /W4)
else()
    target_compile_options (${PROJECT_NAME}  PRIVATE -std=c++14 -Wall -Wextra -Wpedantic -Wfatal-errors)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders/
)
