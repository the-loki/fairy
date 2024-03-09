//
// Created by loki on 2024/3/9.
//

#include <runtime/render/system.h>

namespace fairy::runtime::render {

void Initialize(flecs::world & world) {
	world.system<GraphicsContext, const Window>().kind(flecs::OnStart).each(SetupGraphicsContext);
	world.system<GraphicsContext, const Window>().kind(flecs::PreUpdate).each(SetupSwapChain);
}

}