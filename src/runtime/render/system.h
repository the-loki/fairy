//
// Created by loki on 2024/3/9.
//


#pragma once

#include <runtime/render/component/graphics_context.h>
#include <runtime/window/component/window.h>
#include <flecs.h>

namespace fairy::runtime::render {

using Window = fairy::runtime::window::Window;

void Initialize(flecs::world & world);
void SetupGraphicsContext(GraphicsContext &ctx, const Window &window);
void SetupSwapChain(GraphicsContext &ctx, const Window &window);

}