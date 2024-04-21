//
// Created by loki on 2024/3/4.
//


#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string_view>
#include <memory>

namespace fairy::runtime {
class Engine;
}

namespace fairy::runtime::window {

class Window {
public:
	void Update();
	static std::shared_ptr<Window> CreateDefault();
	bool Initialize(const std::weak_ptr<runtime::Engine> &engine);
protected:
	bool CreateWindow();
public:
	std::string title_;
	glm::ivec2 size_{};
	GLFWwindow *window_ = nullptr;
	std::weak_ptr<runtime::Engine> engine_;
};

}