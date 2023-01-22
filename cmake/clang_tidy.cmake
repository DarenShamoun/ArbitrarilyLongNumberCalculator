find_program(CLANGTIDY clang-tidy)
if(CLANGTIDY)
  set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
  message(STATUS "Running  ${CLANGTIDY} on ${CMAKE_SOURCE_DIR}")
else()
  message(WARNING "clang-tidy requested but executable not found")
endif()

