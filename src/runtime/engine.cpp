//
// Created by loki on 2024/2/16.
//


#include <iostream>
#include <thread>
#include <runtime/engine.h>
#include <runtime/window/window.h>
#include <runtime/gfx//gfx.h>
#include <runtime/render/render.h>

namespace fairy::runtime {

bool Engine::Initialize() {
	world_ = std::make_shared<flecs::world>();
	auto threadNum = static_cast<int32_t>(std::thread::hardware_concurrency());
	world_->set_threads(threadNum);
	world_->set<flecs::Rest>({});

	window_ = window::Window::CreateDefault();

	if (!window_->Initialize(shared_from_this())) {
		return false;
	}

	gfx_ = std::make_shared<gfx::Gfx>();

	if (!gfx_->Initialize(shared_from_this())) {
		return false;
	}

	render_ = std::make_shared<render::Render>(shared_from_this());
	return true;
}

void Engine::Start() const {
	struct CoreHolder { void *x; } holder{};

	world_->entity().set(holder);
	world_->system<const CoreHolder>().kind(flecs::PreUpdate).each([&](const CoreHolder &) {
		window_->Update();
		gfx_->Update();
	});

	while (world_->progress()) {

	}

	world_->quit();
}

std::shared_ptr<Engine> Engine::Create() {
	auto engine = new Engine();
	return std::shared_ptr<Engine>(engine);
}

void Engine::Quit() const {
	if (world_) {
		world_->quit();
	}
}

}
