//
// Created by loki on 2024/3/9.
//


#include <runtime/window/component/window.h>
#include <runtime/render/component/graphics_context.h>
#include <flecs.h>

namespace fairy::runtime::window {

static void PrintGlfwError(int error, const char *description) {
	printf("GLFW Error %d: %s\n", error, description);
}

void SetupGlfwWindow(flecs::entity entity, Window &window) {
	using GraphicsContext = fairy::runtime::render::GraphicsContext;

	glfwSetErrorCallback(PrintGlfwError);

	if (!glfwInit()) {
		entity.destruct();
		return;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	auto title = window.title_;
	auto size = window.size_;
	window.window_ = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);

	if (!window.window_) {
		entity.destruct();
		glfwTerminate();
		return;
	}

	glfwShowWindow(window.window_);
	entity.set(GraphicsContext{});
}

}