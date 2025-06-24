cmake_minimum_required(VERSION 3.10)

if(WIN32)
  include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("taoq")

find_package(fmt REQUIRED)

link_libraries(fmt::fmt)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(taoq ${SOURCES})

install(TARGETS taoq DESTINATION bin)
install(IMPORTED_RUNTIME_ARTIFACTS fmt::fmt DESTINATION bin)
