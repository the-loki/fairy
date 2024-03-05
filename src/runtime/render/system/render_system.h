//
// Created by loki on 2024/3/5.
//


#pragma once

#include <flecs.h>
#include <runtime/render/component/graphics_context.h>
#include "runtime/window/component/window.h"

namespace fairy::runtime::render {

class RenderSystem {
	using Window = fairy::runtime::window::Window;

public:
	static void Initialize(flecs::world &world);
private:
	static void SetupGraphicsContext(GraphicsContext &graphics_context, const Window &window);
	static void SetupSwapChain(GraphicsContext &graphics_context, const Window &window);
};

}

