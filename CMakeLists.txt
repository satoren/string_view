# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.7)
project (string_view)

add_executable(string_view_test string_view.hpp string_view_test.cpp)

add_executable(constexpr_string_test constexpr_string.hpp constexpr_string_test.cpp)


#check for address sanitizer support
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 4.8)
      set(HAVE_FLAG_SANITIZE_ADDRESS TRUE)
    endif()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    if (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 3.2)
      set(HAVE_FLAG_SANITIZE_ADDRESS TRUE)
    endif()
endif()
if(CYGWIN OR WIN32)
      unset(HAVE_FLAG_SANITIZE_ADDRESS)
endif()

if(HAVE_FLAG_SANITIZE_ADDRESS AND NOT DISABLE_ADDRESS_SANITIZER)
SET_TARGET_PROPERTIES(string_view_test PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
SET_TARGET_PROPERTIES(string_view_test PROPERTIES LINK_FLAGS "-fsanitize=address")
endif(HAVE_FLAG_SANITIZE_ADDRESS AND NOT DISABLE_ADDRESS_SANITIZER)

enable_testing()
if(COVERAGE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage -coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -W -fprofile-arcs -ftest-coverage -coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif(COVERAGE)
add_test(
  NAME string_view_test
  COMMAND $<TARGET_FILE:string_view_test>)
add_test(
  NAME constexpr_string_test
  COMMAND $<TARGET_FILE:constexpr_string_test>)
