//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/window/system/window_system.h>

namespace fairy::runtime::window {

inline void Initialize(flecs::world & world) {
	WindowSystem::Initialize(world);
}

}

