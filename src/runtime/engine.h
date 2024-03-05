//
// Created by loki on 2024/2/16.
//

#pragma once

#include <memory>
#include <runtime/platform/window.h>
#include <flecs.h>

namespace fairy::runtime {

class Engine : public core::NonCopyableAndMovable {
public:
	Engine() = default;
	~Engine() = default;

	virtual void Start();
	virtual bool Init();

protected:
	[[nodiscard]] bool ShouldFinish() const;
	void WindowLoop() const;

public:
	std::shared_ptr<flecs::world> world_ = nullptr;
	std::shared_ptr<platform::Window> window_ = nullptr;
};

}
