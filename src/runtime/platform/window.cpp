//
// Created by 57470 on 2024/2/18.
//

#include <runtime/platform/Window.h>
#include <webgpu_extra.h>

namespace fairy::runtime::platform {

static void print_glfw_error(int error, const char *description) {
	printf("GLFW Error %d: %s\n", error, description);
}

void Window::Init(const InitWindowConfig &config) {
	size_ = config.size;
	title_ = config.title;
}

bool Window::InitWebgpu() {
	graphics_context_ = std::make_shared<graphics_context_>();
	return graphics_context_->Init(Window);
}

bool Window::Open() {
	glfwSetErrorCallback(print_glfw_error);

	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	Window = glfwCreateWindow(size_.x, size_.y, title_.data(), nullptr, nullptr);

	if (!Window) {
		glfwTerminate();
		return false;
	}

	if (!InitWebgpu()) {
		graphics_context_.reset();
		glfwDestroyWindow(Window);
		Window = nullptr;
		glfwTerminate();
		return false;
	}

	glfwShowWindow(Window);
	return true;
}

Window::~Window() {
	graphics_context_.reset();

	if (Window) {
		glfwDestroyWindow(Window);
		Window = nullptr;
		glfwTerminate();
	}
}

bool Window::ShouldClose() const {
	if (!Window) {
		return true;
	}

	return glfwWindowShouldClose(Window);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::GetFramebufferSize() {
	glfwGetFramebufferSize(Window, &(this->size_.x), &(this->size_.y));
}

}