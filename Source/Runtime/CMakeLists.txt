project(fairy)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/Source/Runtime/*.cpp")

add_library(FairyRuntime)
target_sources(FairyRuntime PRIVATE ${SOURCE_FILES})

target_link_libraries(FairyRuntime PUBLIC glm)
target_link_libraries(FairyRuntime PUBLIC webgpu)
target_link_libraries(FairyRuntime PUBLIC webgpu_extra)
target_link_libraries(FairyRuntime PUBLIC glfw)
target_link_libraries(FairyRuntime PUBLIC glfw3webgpu)
target_link_libraries(FairyRuntime PUBLIC imgui)
