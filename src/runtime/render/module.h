//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/render/system.h>

namespace fairy::runtime::render {

inline void InitializeModule(flecs::world & world) {
	Initialize(world);
}

}

