cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

project(lesson04)


# 设置SDL2目录
set(SDL2_DIR "D:/Dev/SDL2/2.0.18")
# 设置SDL2头文件目录
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
# 设置SDL2库文件目录
set(SDL2_LIBRARIES_DIR "${SDL2_DIR}/lib/x64")

aux_source_directory(src SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# 设置包含头文件目录
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${SDL2_INCLUDE_DIR}
        )

# 设置链接库文件
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${SDL2_LIBRARIES_DIR}/SDL2.lib
        ${SDL2_LIBRARIES_DIR}/SDL2main.lib
        )

# 复制SDL2.dll到构建目录
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIBRARIES_DIR}/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )

# 复制资源文件
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/gfx"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx
        )