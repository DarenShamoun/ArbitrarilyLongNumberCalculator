#
# This function will prevent in-source builds
function(AssureOutOfSourceBuilds)
  # make sure the user doesn't play dirty with symlinks
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)
  get_filename_component(curbin "${CMAKE_CURRENT_BINARY_DIR}" REALPATH)

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}" OR
      EXISTS "${curbin}/CMakeLists.txt")
    message("######################################################")
    message("Warning: in-source builds are disabled")
    message("Please create a separate build directory and run `cmake ..` from there")
    message("NOTE: cmake has created CMakeCache.txt and CMakeFiles/*.")
    message("You must delete them, or cmake will refuse to work.")
    message("######################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

assureoutofsourcebuilds()

