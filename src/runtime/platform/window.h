//
// Created by loki on 2024/2/18.
//

#pragma once

#include <runtime/core/common/object.h>
#include <runtime/platform/graphics_context.h>

#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <string_view>
#include <glm/glm.hpp>
#include <memory>

namespace fairy::runtime::platform {

struct InitWindowConfig {
	bool resizable_ = false;
	std::string_view title_;
	glm::ivec2 size_{};

	InitWindowConfig() : resizable_(false), title_("Fairy"), size_{1280, 720} {}
};

class Window : public core::Object {
public:
	Window() = default;
	~Window() override;

	virtual bool Open();
	virtual bool InitWebgpu();
	virtual void Init(const InitWindowConfig &config);

	static void PollEvents();
	void GetFramebufferSize();
	[[nodiscard]] bool ShouldClose() const;

public:
	std::string title_;
	glm::ivec2 size_{};
	GLFWwindow *window_ = nullptr;
	std::shared_ptr<GraphicsContext> graphics_context_ = nullptr;
};

}

