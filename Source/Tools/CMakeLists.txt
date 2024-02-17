file(GLOB_RECURSE EDITOR_SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/tools/editor/*.cpp")

add_executable(FairyEditor)
target_sources(FairyEditor PRIVATE ${EDITOR_SOURCE_FILES})

target_link_libraries(FairyEditor PRIVATE FairyRuntime)
