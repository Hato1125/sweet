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
  ${LIBSDL2}
  ${LIBSDL2_TTF}
  ${LIBSDL2_IMG}
  ${PROJECT_NAME}
)
