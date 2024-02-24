//
// Created by loki on 2024/2/16.
//

#pragma once

#include <memory>
#include <runtime/platform/window.h>
#include <runtime/core/ecs/registry.h>

namespace fairy::runtime {

struct InitEngineConfig {
	platform::InitWindowConfig window_config_;
};

class Engine : public core::Object {
public:
	Engine() = default;
	~Engine() override = default;

	virtual void StartMainLoop();
	virtual bool Init(const InitEngineConfig &config);

protected:
	[[nodiscard]] bool ShouldFinish() const;
	void MainLoopStep() const;

public:
	std::shared_ptr<platform::Window> window_ = nullptr;
	std::shared_ptr<core::ecs::Registry> registry_ = nullptr;
};

}
