//
// Created by loki on 2024/2/16.
//

#pragma once

#include <runtime/core/common/type_traits.h>
#include <memory>
#include <flecs.h>

namespace fairy::runtime {

class Engine : public core::NonCopyableAndMovable {
public:
	Engine() = default;
	~Engine() = default;

	virtual void Start();
	virtual bool Initialize();

public:
	std::shared_ptr<flecs::world> world_ = nullptr;
};

}
