//
// Created by loki on 2024/3/9.
//


#include <runtime/render/component/graphics_context.h>
#include <runtime/window/component/window.h>

using Window = fairy::runtime::window::Window;

namespace fairy::runtime::render {

void SetupSwapChain(GraphicsContext &graphics_context, const Window &window) {
	if (window.size_.x!=graphics_context.swap_chain_size_.x || window.size_.y!=graphics_context.swap_chain_size_.y) {

	}
}

}