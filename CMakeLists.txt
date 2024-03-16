cmake_minimum_required(VERSION 3.8)

project(sweet_engine)
set(VERSION 0.0.1)
set(LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Isn't stdlibc++ supported yet?
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/module)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

set(LIBSDL2 SDL2::SDL2)
set(LIBSDL2_TTF SDL2_ttf::SDL2_ttf)
set(LIBSDL2_IMG SDL2_image::SDL2_image)

include(add_include_directories)
include(add_source_files)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_compile_options(-O1)
  add_subdirectory(src)

  # Output include files.
  message("---- Output include files ----")
  file(GLOB SUBDIRECTORIES LIST_DIRECTORIES ON ${PROJECT_SOURCE_DIR}/src/*)
  file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
  foreach(DIRECTORY ${SUBDIRECTORIES})
    if(IS_DIRECTORY ${DIRECTORY})
      file(GLOB HEADER_FILES ${DIRECTORY}/**.hpp)
      foreach(FILE ${HEADER_FILES})
        message("Output: ${FILE}")
        configure_file(${FILE} ${CMAKE_BINARY_DIR}/include)
      endforeach()
    endif()
  endforeach()
else()
  add_compile_options(-O0)
  add_subdirectory(src)
  add_subdirectory(test)
endif()
