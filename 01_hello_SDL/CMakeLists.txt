cmake_minimum_required(VERSION 3.18)

project(lesson01)

set(CMAKE_C_STANDARD 11)

# 设置SDL2目录
set(SDL2_DIR "D:/Dev/SDL2/2.0.18")
# 设置SDL2头文件目录
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
# 设置SDL2库文件目录
set(SDL2_LIBRARIES_DIR "${SDL2_DIR}/lib/x64")

aux_source_directory(src SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${SDL2_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${SDL2_LIBRARIES_DIR}/SDL2.lib
        ${SDL2_LIBRARIES_DIR}/SDL2main.lib
        )

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIBRARIES_DIR}/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )