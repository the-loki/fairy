//
// Created by loki on 2024/2/16.
//

#include <runtime/engine.h>

namespace fairy::runtime {

bool Engine::Init(const InitEngineConfig &config) {
	window_ = std::make_shared<platform::Window>();
	window_->Init(config.window_config_);

	if (!window_->Open()) {
		window_.reset();
		return false;
	}

	return true;
}

void Engine::StartMainLoop() {
#ifndef __EMSCRIPTEN__
	while (!ShouldFinish()) {
		MainLoopStep();
	}
#else
	emscripten_set_main_loop_arg(main_loop_step, window, 0, false);
#endif
}

bool Engine::ShouldFinish() const {
	return window_->ShouldClose();
}

void Engine::MainLoopStep() const {
	window_->PollEvents();
	window_->GetFramebufferSize();
	const auto frame_buffer_size = window_->size_;
}

}
