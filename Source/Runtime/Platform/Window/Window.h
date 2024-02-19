//
// Created by loki on 2024/2/18.
//

#pragma once

#include <Runtime/Core/Object.h>
#include <Runtime/Core/Math/Math.hpp>
#include <Runtime/Platform/Window/GraphicsContext.h>
#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <string_view>
#include <memory>

namespace fairy::runtime::platform {

struct CreateWindowConfig {
  bool resizable = false;
  std::string_view title;
  core::math::ivec2 size{};

  CreateWindowConfig()
		  :resizable(false), title("Fairy"), size{1280, 720} { }
};

class Window : public core::Object {
public:
	explicit Window(const CreateWindowConfig& config);
	~Window() override;

	virtual bool open();
	virtual bool init_webgpu();

	[[nodiscard]] bool should_close() const;
	static void poll_events();
	void get_framebuffer_size();

public:
	std::string title;
	GLFWwindow* window;
	core::math::ivec2 size{};
	std::shared_ptr<GraphicsContext> graphics_context;
};

}

