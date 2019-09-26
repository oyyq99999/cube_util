cmake_minimum_required(VERSION 3.0)

project(cube_util_test VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName test_${testSrc} NAME_WE)
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
endforeach(testSrc)