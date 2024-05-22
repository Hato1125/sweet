macro(request_package PACKAGE_NAME ERROR_MESSAGE)
  find_package(${PACKAGE_NAME} REQUIRED)
  if(NOT ${PACKAGE_NAME}_FOUND)
    message(FATAL_ERROR ${ERROR_MESSAGE})
  endif()
endmacro()