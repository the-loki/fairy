//
// Created by loki on 2024/3/5.
//

#include <runtime/window/system/window_system.h>
#include <runtime/render/component/graphics_context.h>
#include <thread>

using GraphicsContext = fairy::runtime::render::GraphicsContext;

namespace fairy::runtime::window {

static void PrintGlfwError(int error, const char *description) {
	printf("GLFW Error %d: %s\n", error, description);
}

void WindowSystem::Initialize(flecs::world &world) {
	world.entity().set(fairy::runtime::window::Window::CreateDefault());
	world.system<Window>().kind(flecs::OnStart).write<Window>().each(WindowSystem::SetupGlfwWindow);
	world.system<Window>().kind(flecs::PreUpdate).write<GraphicsContext>().each(WindowSystem::UpdateWindow);
}

void WindowSystem::UpdateWindow(flecs::entity entity, Window &window) {
	if(glfwWindowShouldClose(window.window_)){
		entity.world().quit();
		return;
	}

	glfwPollEvents();
	glfwGetFramebufferSize(window.window_, &(window.size_.x), &(window.size_.y));
}

void WindowSystem::SetupGlfwWindow(flecs::entity entity, Window &window) {
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