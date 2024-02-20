add_library(shared_headers INTERFACE)

#wgpu
set(WGPU_DIR ${CMAKE_SOURCE_DIR}/thirdparty/wgpu-v0.17.2.1)
set(WGPU_LIB_DIR ${WGPU_DIR}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM_NAME})
set(WGPU_LIB_NAME ${CMAKE_STATIC_LIBRARY_PREFIX}wgpu_native${CMAKE_STATIC_LIBRARY_SUFFIX})

add_library(webgpu INTERFACE)
target_link_directories(webgpu INTERFACE ${WGPU_LIB_DIR})
target_include_directories(webgpu INTERFACE ${WGPU_DIR})
target_link_libraries(webgpu INTERFACE ${WGPU_LIB_NAME})

if (WIN32)
    target_link_libraries(webgpu INTERFACE ws2_32 Userenv ntdll d3dcompiler bcrypt)
endif ()

#glfw3
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glfw-3.3.9)
set(GLFW_INSTALL OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${GLFW_DIR})

#glfw3webgpu
set(GLFW3WGPU_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glfw3webgpu-v1.1.0)
add_subdirectory(${GLFW3WGPU_DIR})

#webgpu-extra
set(WEBGPU_EXTRA_DIR ${CMAKE_SOURCE_DIR}/thirdparty/webgpu_extra-v0.0.1)
add_subdirectory(${WEBGPU_EXTRA_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui-1.90.3)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

add_library(imgui)
target_sources(imgui PUBLIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_BACKENDS_DIR}/imgui_impl_wgpu.cpp)

target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_BACKENDS_DIR})
target_link_libraries(imgui PUBLIC glfw webgpu)

#glm
set(GLM_DIR ${CMAKE_SOURCE_DIR}/thirdparty/glm-1.0.0)
add_subdirectory(${GLM_DIR})


#taskflow
set(TASK_FLOW_DIR ${CMAKE_SOURCE_DIR}/thirdparty/taskflow-3.6.0)
set(TF_BUILD_TESTS OFF)
set(TF_BUILD_EXAMPLES OFF)
set(CMAKE_VERBOSE_MAKEFILE OFF)
add_subdirectory(${TASK_FLOW_DIR})
