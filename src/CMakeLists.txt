add_library(${PROJECT_NAME})

add_source_files(${PROJECT_NAME} cpp)
add_include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBSDL2} ${LIBSDL2_TTF} ${LIBSDL2_IMG})
