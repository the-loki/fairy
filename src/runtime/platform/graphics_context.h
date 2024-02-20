//
// Created by loki on 2024/2/19.
//


#pragma once

#include <runtime/core/common/object.h>
#include <webgpu/webgpu.h>
#include <GLFW/glfw3.h>

namespace fairy::runtime::platform {

class graphics_context : public core::Object {
public:
	graphics_context() = default;
	~graphics_context() override;

	virtual bool init(GLFWwindow *window);

public:
	WGPUDevice device = nullptr;
	WGPUSurface surface = nullptr;
	WGPUAdapter adapter = nullptr;
	WGPUInstance instance = nullptr;
	WGPUSwapChain swap_chain = nullptr;
	WGPUTextureFormat texture_format = WGPUTextureFormat::WGPUTextureFormat_Undefined;
};

}

