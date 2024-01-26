cmake_minimum_required(VERSION 3.8)

project(sweet_engine)
set(VERSION 0.0.0)
set(LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/module)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

set(LIBSDL2 SDL2::SDL2)
set(LIBSDL2_TTF SDL2_ttf::SDL2_ttf)
set(LIBSDL2_IMG SDL2_image::SDL2_image)

include(GetFiles)
add_subdirectory(src)
add_subdirectory(test)
