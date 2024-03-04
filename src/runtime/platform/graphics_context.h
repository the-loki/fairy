//
// Created by loki on 2024/2/19.
//


#pragma once

#include <runtime/core/common/type_traits.h>
#include <webgpu/webgpu.h>
#include <GLFW/glfw3.h>

namespace fairy::runtime::platform {

class GraphicsContext final : public core::NonCopyableAndMovable {
public:
	GraphicsContext() = default;
	~GraphicsContext();

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

