//
// Created by loki on 2024/3/5.
//

#pragma once

#include <flecs.h>
#include <runtime/window/component/window.h>

namespace fairy::runtime::window {

void Initialize(flecs::world & world);
void SetupGlfwWindow(flecs::entity entity, Window &window);
void UpdateWindow(flecs::entity entity, Window &window);

}
