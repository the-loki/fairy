//
// Created by 57470 on 2024/2/18.
//

#include "WebGPUWindow.h"
#include <webgpu_extra.h>

namespace fairy::runtime::platform {

static void print_glfw_error(int error, const char* description)
{
	printf("GLFW Error %d: %s\n", error, description);
}

WebGPUWindow::WebGPUWindow(std::string_view title, core::math::ivec2 size)
		:window(nullptr), size(size), title(title)
{
}

bool WebGPUWindow::init_webgpu()
{
	using namespace webgpu_extra;





	return true;
}

bool WebGPUWindow::open()
{
	glfwSetErrorCallback(print_glfw_error);

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	this->window = glfwCreateWindow(size.x, size.y, title.data(), nullptr, nullptr);

	if (!this->window) {
		glfwTerminate();
		return false;
	}

	if (!this->init_webgpu()) {
		glfwDestroyWindow(this->window);
		glfwTerminate();
		return false;
	}

	return true;
}

}