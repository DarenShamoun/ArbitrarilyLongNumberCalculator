# Common capabilities for all projects
include (cmake/default_settings.cmake)
include (cmake/prevent_source_builds.cmake)
include (cmake/compiler_warnings.cmake)
include (cmake/doctest.cmake)
include (cmake/static_analyzers.cmake)

# Link to this placeholder to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link to this placeholder to use the warnings specified in compiler_warnings.cmake
add_library(project_warnings INTERFACE)

set_project_warnings(project_warnings)

# Link to this placeholder to promote all warning to errors (compiler_warnings.cmake)
add_library(project_errors INTERFACE)
set_project_errors(project_errors)

function(check_source)
  foreach(fname ${ARGN})
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${fname}")
      message(STATUS "Pass. ${fname} exists.")
    else()
      message(FATAL_ERROR "*** Config failure! ${fname} not found.")
    endif()
  endforeach()
endfunction()

