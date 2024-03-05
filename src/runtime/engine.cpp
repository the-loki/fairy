//
// Created by loki on 2024/2/16.
//

#include <runtime/engine.h>
#include <iostream>
#include <thread>
#include <runtime/window/module.h>

namespace fairy::runtime {

bool Engine::Init() {
//	window_ = std::make_shared<platform::Window>();
//	window_->Init(config.window_config_);
//
//	if (!window_->Open()) {
//		window_.reset();
//		return false;
//	}

	world_ = std::make_shared<flecs::world>();
	auto threadNum = static_cast<int32_t>(std::thread::hardware_concurrency());
	world_->set_threads(threadNum);

	return true;
}

void Engine::Start() {
	window::Initialize(*world_);


	while (world_->progress()) {
//		WindowLoop();
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
