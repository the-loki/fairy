//
// Created by loki on 2024/3/4.
//


#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string_view>

namespace fairy::runtime::window {

struct Window {
	std::string title_;
	glm::ivec2 size_{};
	GLFWwindow *window_ = nullptr;
};

}