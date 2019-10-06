cmake_minimum_required(VERSION 3.1)

project(cube_util_test VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
find_program(_cpplint cpplint)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} TEST_SRCS)

foreach(testSrc ${TEST_SRCS})
  get_filename_component(testFileName ${testSrc} NAME_WE)
  set(testName test_${testFileName})
  add_executable(${testName} ${testSrc})
  target_compile_features(${testName} PUBLIC cxx_auto_type)
  target_link_libraries(${testName} cube_util Boost::unit_test_framework)
  target_compile_definitions(${testName} PRIVATE BOOST_TEST_DYN_LINK)
  set_target_properties(${testName} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/testBin)
  add_test(NAME ${testName}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/testBin
    COMMAND ${CMAKE_BINARY_DIR}/testBin/${testName}
  )

  if (_cpplint)
    file(GLOB_RECURSE LINT_SRC_FILES
      *.cpp
    )
    add_custom_command(TARGET ${testName}
      PRE_BUILD COMMAND ${_cpplint} --quiet ${LINT_SRC_FILES}
      COMMENT "linting ${testName}")
  endif()
endforeach(testSrc)
