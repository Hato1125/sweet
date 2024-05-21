add_library(${PROJECT_NAME})

add_source_files(
  ${PROJECT_NAME} PRIVATE
  cpp
)

add_include_directories(
  ${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  SDL2::SDL2
  SDL2_image::SDL2_image
  SDL2_ttf::SDL2_ttf
)
