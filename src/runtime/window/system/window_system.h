//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/window/component/window.h>

namespace fairy::runtime::window {

class WindowSystem {
public:
	static void Initialize(flecs::world& world);
protected:
	static void SetupGlfwWindow(flecs::entity entity, Window& window);
	static void UpdateWindow(flecs::entity entity, Window &window);
};

}
