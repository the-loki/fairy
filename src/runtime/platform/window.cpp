//
// Created by 57470 on 2024/2/18.
//

#include <runtime/platform/Window.h>
#include <webgpu_extra.h>

namespace fairy::runtime::platform {

static void PrintGlfwError(int error, const char *description) {
	printf("GLFW Error %d: %s\n", error, description);
}

void Window::Init(const InitWindowConfig &config) {
	size_ = config.size_;
	title_ = config.title_;
}

bool Window::InitWebgpu() {
	graphics_context_ = std::make_shared<GraphicsContext>();
	return graphics_context_->Init(window_);
}

bool Window::Open() {
	glfwSetErrorCallback(PrintGlfwError);

	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window_ = glfwCreateWindow(size_.x, size_.y, title_.data(), nullptr, nullptr);

	if (!window_) {
		glfwTerminate();
		return false;
	}

	if (!InitWebgpu()) {
		graphics_context_.reset();
		glfwDestroyWindow(window_);
		window_ = nullptr;
		glfwTerminate();
		return false;
	}

	glfwShowWindow(window_);
	return true;
}

Window::~Window() {
	graphics_context_.reset();

	if (window_) {
		glfwDestroyWindow(window_);
		window_ = nullptr;
		glfwTerminate();
	}
}

bool Window::ShouldClose() const {
	if (!window_) {
		return true;
	}

	return glfwWindowShouldClose(window_);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::GetFramebufferSize() {
	glfwGetFramebufferSize(window_, &(this->size_.x), &(this->size_.y));
}

}