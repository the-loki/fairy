//
// Created by loki on 2024/2/16.
//

#include <runtime/engine.h>
#include <iostream>

namespace fairy::runtime {

bool Engine::Init(const InitEngineConfig &config) {
	window_ = std::make_shared<platform::Window>();
	window_->Init(config.window_config_);

	if (!window_->Open()) {
		window_.reset();
		return false;
	}

	world_ = std::make_shared<flecs::world>();

	return true;
}

void Engine::Start() {
	while (!ShouldFinish() && world_->progress()) {
		WindowLoop();
	}

	world_->quit();
}

bool Engine::ShouldFinish() const {
	return window_->ShouldClose();
}

void Engine::WindowLoop() const {
	window_->PollEvents();
	window_->GetFramebufferSize();
	const auto frame_buffer_size = window_->size_;
}

}
