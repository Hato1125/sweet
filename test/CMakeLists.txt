add_executable(${PROJECT_NAME}_test)

add_source_files(
  ${PROJECT_NAME}_test PRIVATE
  cpp
)

add_include_directories(
  ${PROJECT_NAME}_test PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  ${PROJECT_NAME}_test PRIVATE
  SDL2::SDL2
  SDL2_image::SDL2_image
  SDL2_ttf::SDL2_ttf
  ${PROJECT_NAME}
)
