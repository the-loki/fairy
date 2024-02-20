//
// Created by loki on 2024/2/18.
//

#pragma once

#include <runtime/core/math/math.h>
#include <runtime/core/common/object.h>
#include <runtime/platform/graphics_context.h>

#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <string_view>
#include <memory>

namespace fairy::runtime::platform {

struct InitWindowConfig {
	bool resizable = false;
	std::string_view title;
	core::math::ivec2 size{};

	InitWindowConfig() : resizable(false), title("Fairy"), size{1280, 720} {}
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
	core::math::ivec2 size_{};
	GLFWwindow *window_ = nullptr;
	std::shared_ptr<graphics_context> graphics_context_ = nullptr;
};

}

