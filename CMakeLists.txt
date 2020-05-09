cmake_minimum_required(VERSION 3.16)

project(VISQOL LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(abseil
                        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
                        GIT_PROGRESS TRUE
                        USES_TERMINAL_DOWNLOAD
                        TRUE)

FetchContent_Declare(armadillo
                        GIT_REPOSITORY https://gitlab.com/conradsnicta/armadillo-code.git
                        GIT_TAG 9.900.x
                        GIT_PROGRESS TRUE
                        USES_TERMINAL_DOWNLOAD
                        TRUE)

FetchContent_Declare(pffft
                        GIT_REPOSITORY https://github.com/marton78/pffft.git
                        GIT_PROGRESS TRUE
                        USES_TERMINAL_DOWNLOAD
                        TRUE)


FetchContent_GetProperties(abseil, armadillo, pffft)
if(NOT abseil_POPULATED)
  FetchContent_Populate(abseil)
  set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
  #add_subdirectory(${abseil_SOURCE_DIR})

  add_subdirectory(${abseil_SOURCE_DIR} ${abseil_BINARY_DIR})
  add_library(standalone_absl INTERFACE IMPORTED GLOBAL)
  target_link_libraries(standalone_absl INTERFACE absl_synchronization)
endif()

if(NOT armadillo_POPULATED)
  FetchContent_Populate(armadillo)
  add_subdirectory(${armadillo_SOURCE_DIR})
endif()

if(NOT pffft_POPULATED)
  FetchContent_Populate(pffft)
  set(USE_BENCH_GREEN=OFF)
  set(USE_BENCH_KISS=OFF)
  add_subdirectory(${pffft_SOURCE_DIR})
endif()

add_library(visqol)
target_include_directories(visqol PRIVATE src/include)
target_include_directories(visqol PRIVATE ${abseil_SOURCE_DIR})
target_include_directories(visqol PRIVATE ${armadillo_SOURCE_DIR}/include)
target_include_directories(visqol PRIVATE ${pffft_SOURCE_DIR})
target_link_libraries(standalone_absl)
if (MSVC)
  target_compile_definitions(visqol PRIVATE _USE_MATH_DEFINES)
endif()



add_subdirectory(src)
