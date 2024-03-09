//
// Created by loki on 2024/2/16.
//


#include <iostream>
#include <thread>
#include <runtime/engine.h>
#include <runtime/window/module.h>
#include <runtime/render/module.h>

namespace fairy::runtime {

bool Engine::Initialize() {
	world_ = std::make_shared<flecs::world>();
	auto threadNum = static_cast<int32_t>(std::thread::hardware_concurrency());
	world_->set_threads(threadNum);
	world_->set<flecs::Rest>({});

	return true;
}

void Engine::Start() {
	window::InitializeModule(*world_);
	render::InitializeModule(*world_);

	while (world_->progress()) {
	}

	world_->quit();
}

}
