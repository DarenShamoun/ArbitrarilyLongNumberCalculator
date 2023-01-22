include (CTest)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/../extern/doctest.h")
  file(DOWNLOAD https://raw.githubusercontent.com/onqtam/doctest/2.4.6/doctest/doctest.h
    "${CMAKE_SOURCE_DIR}/../extern/doctest.h"
    STATUS DOWNLOAD_STATUS
    EXPECTED_HASH MD5=1494db8a28035bcf6caeea817c4b2b65
    )
  message(STATUS " doctest download status: ${DOWNLOAD_STATUS}")
endif()
file(MD5 "${CMAKE_SOURCE_DIR}/../extern/doctest.h" DT_HASH)
if (${DT_HASH} STREQUAL "d41d8cd98f00b204e9800998ecf8427e")
  message(NOTICE " === ")
  message(NOTICE " doctest.h is empty")
  message(NOTICE " === ")
endif()

add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE ${CMAKE_SOURCE_DIR}/../extern)

function(make_test name)
  if (${ARGC} EQUAL 1)
    add_executable(${name} ${name}.cpp) 
  else()
    add_executable(${name} ${name}.cpp ${ARGN}) 
  endif()
  if (TARGET ${CMAKE_PROJECT_NAME})
    target_link_libraries(${name} ${CMAKE_PROJECT_NAME} doctest)
  else()
    target_link_libraries(${name} doctest)
  endif()
  target_compile_definitions(${name} PRIVATE DOCTEST_CONFIG_NO_POSIX_SIGNALS)
  add_test(NAME ${name} COMMAND ${name})
  set_tests_properties(${name} PROPERTIES TIMEOUT 3)
endfunction()

function(make_test_strict name)

  make_test(${name} ${ARGN})
  target_link_libraries(${name} project_errors)

endfunction()
