project(fairy_runtime)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/runtime/*.cpp")

add_library(fairy_runtime)
target_sources(fairy_runtime PRIVATE ${SOURCE_FILES})

target_link_libraries(fairy_runtime PUBLIC glm)
target_link_libraries(fairy_runtime PUBLIC webgpu)
target_link_libraries(fairy_runtime PUBLIC webgpu_extra)
target_link_libraries(fairy_runtime PUBLIC glfw)
target_link_libraries(fairy_runtime PUBLIC glfw3webgpu)
target_link_libraries(fairy_runtime PUBLIC imgui)
target_link_libraries(fairy_runtime PUBLIC Taskflow)
