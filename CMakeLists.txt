cmake_minimum_required(VERSION 3.0.2)
project(SANDAL2)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "-Wall -pedantic ${CMAKE_C_FLAGS}")
endif()

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES) # Remove leading or trailing whitespace.

file(GLOB_RECURSE sandal2_sources src/*.c)
add_library(sandal2a ${sandal2_sources})
target_link_libraries(sandal2a
  ${SDL2_LIBRARIES}
  ${SDL2TTF_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES}
  m
  )

add_library(sandal2 SHARED ${sandal2_sources})
target_link_libraries(sandal2
  ${SDL2_LIBRARIES}
  ${SDL2TTF_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES}
  )

file(GLOB ex_dir examples/*)
add_custom_target(examples)
foreach(examples ${ex_dir})
  file(GLOB_RECURSE example_sources ${examples}/*.c)
  get_filename_component(example ${examples} NAME)
  add_executable(${example} EXCLUDE_FROM_ALL ${example_sources})
  target_link_libraries(${example} sandal2a)
  add_dependencies(examples ${example})
endforeach(examples)

add_custom_target(tests
  COMMAND cd ../tests && ./build.sh && ./run.sh)

file(GLOB header src/*.h)

install(
  TARGETS sandal2
  LIBRARY DESTINATION /tmp/lib
  CONFIGURATIONS Release
  )

install(
  FILES ${header}
  DESTINATION /tmp/includes
  )
