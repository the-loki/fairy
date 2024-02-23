//
// Created by loki on 2024/2/19.
//


#pragma once

#include <runtime/core/common/object.h>
#include <webgpu/webgpu.h>
#include <GLFW/glfw3.h>

namespace fairy::runtime::platform {

class GraphicsContext : public core::Object {
public:
	GraphicsContext() = default;
	~GraphicsContext() override;

	virtual bool Init(GLFWwindow *window);

public:
	WGPUDevice device_ = nullptr;
	WGPUSurface surface_ = nullptr;
	WGPUAdapter adapter_ = nullptr;
	WGPUInstance instance_ = nullptr;
	WGPUSwapChain swap_chain_ = nullptr;
	WGPUSupportedLimits supported_limits_{};
	WGPUTextureFormat texture_format_ = WGPUTextureFormat::WGPUTextureFormat_Undefined;
};

}

