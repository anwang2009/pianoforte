cmake_minimum_required(VERSION 3.28)

include_directories(${CMAKE_SOURCE_DIR}/ext/SDL2-2.30.1/include)
include_directories(${CMAKE_SOURCE_DIR}/ext/SDL2_mixer-2.8.0/include)
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/ext/SDL2-2.30.1/lib/x64)
link_directories(${CMAKE_SOURCE_DIR}/ext/SDL2_mixer-2.8.0/lib/x64)

project(pianoforte)

set(SRCS
main.cpp
scene.cpp
core.cpp
player.cpp
)

set(HEADERS
core.h
player.h
scene.h
)

#add_executable(pianoforte main.cpp "scene.cpp" "core.cpp" "core.h" "player.h" "scene.h" "player.cpp")
add_executable(pianoforte "${SRCS}" "${HEADERS}")

target_link_libraries(pianoforte SDL2 SDL2main SDL2_mixer)


if (WIN32)
	file(GLOB sounds ${PROJECT_SOURCE_DIR}/ext/sounds/*)

	add_custom_command(
		TARGET pianoforte POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ext/SDL2-2.30.1/lib/x64/SDL2.dll" "$<TARGET_FILE_DIR:pianoforte>"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ext/SDL2_mixer-2.8.0/lib/x64/SDL2_mixer.dll" "$<TARGET_FILE_DIR:pianoforte>"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sounds}" "$<TARGET_FILE_DIR:pianoforte>"
		COMMAND_EXPAND_LISTS
	)
endif()
