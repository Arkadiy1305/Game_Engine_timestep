cmake_minimum_required (VERSION 3.8)
include(FetchContent)

project ("CMakeProject3")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(OALPP_ENABLE_UNIT_TESTS OFF)
set(OALPP_ENABLE_APPROVAL_TESTS OFF)
set(OALPP_ENABLE_INTEGRATION_TESTS OFF)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject3 "CMakeProject3.cpp" "CMakeProject3.h" "ShaderProgram.h" "ShaderProgram.cpp" "VAO.h"  "stb_image.h" "OverloadedOperators.h" "Sprite.h" "Game.h" "Timer.h"  "Game.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

FetchContent_Declare(
        openalpp
        GIT_REPOSITORY https://github.com/Laguna1989/OpenALpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(openalpp)

target_link_libraries(CMakeProject3 OpenALpp_Lib)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)

FetchContent_MakeAvailable(glm)

target_link_libraries(CMakeProject3 glm)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)