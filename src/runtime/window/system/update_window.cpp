//
// Created by loki on 2024/3/9.
//


#include <runtime/window/component/window.h>
#include <flecs.h>

namespace fairy::runtime::window {

void UpdateWindow(flecs::entity entity, Window &window) {
	if (glfwWindowShouldClose(window.window_)) {
		entity.world().quit();
		return;
	}

	glfwPollEvents();
	glfwGetFramebufferSize(window.window_, &(window.size_.x), &(window.size_.y));
}

}