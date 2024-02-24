//
// Created by loki on 2024/2/23.
//

#include "forward_lighting_pass.h"

namespace fairy::runtime::function::render {

ForwardLightingPass::ForwardLightingPass() : RenderPass("Forward Lighting") {}

void ForwardLightingPass::Setup(const std::weak_ptr<RenderGraph> &graph) {
	RenderPass::Setup(graph);
}

void ForwardLightingPass::Execute() {

}

ForwardLightingPass::~ForwardLightingPass() = default;

}
