
add_library(webgpu_extra INTERFACE)
target_include_directories(webgpu_extra INTERFACE .)
target_link_libraries(webgpu_extra INTERFACE webgpu)