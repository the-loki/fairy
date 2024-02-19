//
// Created by 57470 on 2024/2/18.
//

#include "Window.h"
#include <webgpu_extra.h>

namespace fairy::runtime::platform {

static void print_glfw_error(int error, const char* description)
{
	printf("GLFW Error %d: %s\n", error, description);
}


void Window::init(const InitWindowConfig& config)
{
    size = config.size;
    title = config.title;
}

bool Window::init_webgpu()
{
	graphics_context = std::make_shared<GraphicsContext>();
	return graphics_context->init(window);
}

bool Window::open()
{
	glfwSetErrorCallback(print_glfw_error);

	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return false;
	}

	if (!init_webgpu()) {
		graphics_context.reset();
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
		return false;
	}

	glfwShowWindow(window);
	return true;
}

Window::~Window()
{
	graphics_context.reset();

	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
	}
}

bool Window::should_close() const
{
	if (!window) {
		return true;
	}

	return glfwWindowShouldClose(window);
}

void Window::poll_events()
{
	glfwPollEvents();
}

void Window::get_framebuffer_size()
{
	glfwGetFramebufferSize(window, &(this->size.x), &(this->size.y));
}

}