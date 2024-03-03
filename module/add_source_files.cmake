macro(add_source_files TARGET_NAME EXCEPTION)
  file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**.${EXCEPTION})
  target_sources(${TARGET_NAME} PRIVATE ${SOURCES})
endmacro()
