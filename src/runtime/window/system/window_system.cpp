//
// Created by loki on 2024/3/4.
//



#include <flecs.h>
#include "runtime/window/component/window.h"

namespace fairy::runtime::window {

class WindowSystem {
public:
	static void Load(flecs::world& world);
	static void Start(const Window& window);
	static void Update(const Window& window);
};



void WindowSystem::Load(flecs::world& world_) {
	world_.system<Window>().kind(flecs::OnLoad).each(WindowSystem::Start);
	world_.system<Window>().kind(flecs::OnUpdate).each(WindowSystem::Update);
}

void WindowSystem::Start(const Window &window) {

}

void WindowSystem::Update(const Window &window) {

}

}