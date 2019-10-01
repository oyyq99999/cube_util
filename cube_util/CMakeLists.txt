cmake_minimum_required(VERSION 3.0)

project(cube_util VERSION 0.1.0 LANGUAGES CXX)

set(CUBE_UTIL_SRC_FILES
  src/Utils.cpp
  src/FaceletCubeNNN.cpp
  src/CubieCubeNNN.cpp
  src/CubieCube222.cpp
  src/Cube222Solver.cpp
  src/StaticTables222.cpp
  src/Scrambler.cpp
  src/Scrambler222.cpp
  src/Scramble.cpp
  src/ScrambleNNN.cpp
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
target_compile_features(cube_util
  PUBLIC
    cxx_delegating_constructors
    cxx_auto_type cxx_override
    cxx_nonstatic_member_init
    cxx_defaulted_functions
)
target_link_libraries(cube_util PRIVATE Boost::regex)

export(TARGETS cube_util FILE CubeUtil.cmake)
