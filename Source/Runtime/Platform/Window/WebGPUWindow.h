//
// Created by loki on 2024/2/18.
//

#pragma once

#include <Runtime/Core/Math/Math.hpp>
#include <Runtime/Core/Object.h>
#include <GLFW/glfw3.h>
#include <string_view>
#include <memory>

namespace fairy::runtime::platform {

class WebGPUWindow : public core::Object {
public:
	WebGPUWindow(std::string_view title, core::math::ivec2 size);
	~WebGPUWindow() override;

	virtual bool open();
	virtual bool init_webgpu();

public:
	std::string title;
	GLFWwindow* window;
	core::math::ivec2 size{};
};

}

