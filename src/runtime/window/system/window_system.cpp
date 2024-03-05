//
// Created by loki on 2024/3/5.
//

#include <runtime/window/system/window_system.h>
#include <thread>
#include <iostream>

namespace fairy::runtime::window {

static void PrintGlfwError(int error, const char *description) {
	printf("GLFW Error %d: %s\n", error, description);
}

void WindowSystem::Initialize(flecs::world &world) {
	world.entity().set(fairy::runtime::window::Window::CreateDefault());
	world.system<Window>().kind(flecs::OnStart).each(WindowSystem::OnStart);
	world.system<Window>().kind(flecs::PreUpdate).each(WindowSystem::PreUpdate);
}

void WindowSystem::PreUpdate(flecs::entity entity, Window &window) {
	glfwPollEvents();
	glfwGetFramebufferSize(window.window_, &(window.size_.x), &(window.size_.y));
}

void WindowSystem::OnStart(flecs::entity entity, Window &window) {
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
}

}