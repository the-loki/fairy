//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/render/system/render_system.h>

namespace fairy::runtime::render {

inline void Initialize(flecs::world & world) {
	RenderSystem::Initialize(world);
}

}

