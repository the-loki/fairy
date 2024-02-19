//
// Created by loki on 2024/2/16.
//

#pragma once

#include <memory>
#include <Runtime/Platform/Window/Window.h>

namespace fairy::runtime {

class Engine : public core::Object {
public:
	Engine() = default;
	~Engine() override = default;

	virtual bool init();
	virtual void start_main_loop();

protected:
	[[nodiscard]] bool should_finish() const;
	void main_loop_step() const;

public:

	std::shared_ptr<platform::Window> window = nullptr;
};

}
