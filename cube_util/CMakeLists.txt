cmake_minimum_required(VERSION 3.8)

project(cube_util VERSION 0.1.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CUBE_UTIL_SRC_FILES
  src/Utils.cpp
  src/FaceletCubeNNN.cpp
  src/CubieCubeNNN.cpp
  src/CubieCube222.cpp
  src/Cube222Solver.cpp
  src/CubieCube333.cpp
  src/Scrambler.cpp
  src/Scrambler222.cpp
  src/MoveSequence.cpp
  src/MoveSequenceNNN.cpp
)

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED regex)

add_library(cube_util ${CUBE_UTIL_SRC_FILES})
target_include_directories(cube_util
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src
 )
target_compile_features(cube_util PUBLIC cxx_std_14)
target_link_libraries(cube_util PRIVATE Boost::regex)

find_program(_cpplint cpplint)
if (_cpplint)
  file(GLOB_RECURSE LINT_SRC_FILES
    include/*.hpp
    src/*.hpp
    src/*.cpp
  )
  add_custom_command(TARGET cube_util
    PRE_BUILD COMMAND ${_cpplint} --quiet ${LINT_SRC_FILES}
    COMMENT "linting code")
endif()

find_program(_doxygen doxygen)
if (_doxygen)
  add_custom_command(TARGET cube_util
    POST_BUILD COMMAND ${_doxygen} > /dev/null
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "generating documents")
endif()

export(TARGETS cube_util FILE CubeUtil.cmake)
