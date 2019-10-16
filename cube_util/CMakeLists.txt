cmake_minimum_required(VERSION 3.8)

project(cube_util VERSION 0.1.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CUBE_UTIL_SRC_FILES
  src/utils.cpp
  src/puzzle/facelet_cube_nnn.cpp
  src/puzzle/cubie_cube_nnn.cpp
  src/puzzle/cubie_cube_222.cpp
  src/puzzle/cubie_cube_333.cpp
  src/cube_222_solver.cpp
  src/cube_333_solver.cpp
  src/scrambler.cpp
  src/scrambler_222.cpp
  src/scrambler_333.cpp
  src/move_sequence.cpp
  src/move_sequence_nnn.cpp
)

set(Boost_NO_BOOST_CMAKE ON)
if(IOS)
  set(Boost_USE_STATIC_LIBS ON)
  if(IOS_BOOST_PREFIX)
    find_host_package(Boost REQUIRED regex PATHS ${IOS_BOOST_PREFIX} NO_DEFAULT_PATH)
  else()
    find_host_package(Boost REQUIRED regex)
  endif()
else()
  find_package(Boost REQUIRED regex)
endif()

set(libraryName cube_util)

add_library(${libraryName} ${CUBE_UTIL_SRC_FILES})
target_include_directories(cube_util
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    src
 )
target_compile_features(${libraryName} PUBLIC cxx_std_14)
target_link_libraries(${libraryName} PRIVATE Boost::regex)

if(NOT CPPLINT_ROOT)
  set(CPPLINT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()
find_program(_cpplint cpplint)
if (_cpplint)
  file(GLOB_RECURSE LINT_SRC_FILES
    include/*.hpp
    src/*.hpp
    src/*.cpp
  )
  add_custom_command(TARGET ${libraryName}
    PRE_BUILD COMMAND ${_cpplint} --quiet --root=${CPPLINT_ROOT} ${LINT_SRC_FILES}
    COMMENT "linting code for ${libraryName}")
endif()

find_program(_doxygen doxygen)
if (_doxygen)
  add_custom_command(TARGET ${libraryName}
    POST_BUILD COMMAND ${_doxygen} > /dev/null
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "generating documents")
endif()

export(TARGETS ${libraryName} FILE CubeUtil.cmake)
