file(GLOB_RECURSE EDITOR_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/tools/editor/*.cpp")

add_executable(fairy_editor)
target_sources(fairy_editor PRIVATE ${EDITOR_SOURCE_FILES})

target_link_libraries(fairy_editor PRIVATE fairy_runtime)
