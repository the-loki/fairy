//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/window/system.h>

namespace fairy::runtime::window {

void InitializeModule(flecs::world & world) {
	Initialize(world);
}

}

