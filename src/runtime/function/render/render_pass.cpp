//
// Created by loki on 2024/2/17.
//

#include "render_pass.h"

namespace fairy::runtime::function::render {

RenderPass::RenderPass(const std::string_view &name) : RenderGraphNode(name) {

}

void RenderPass::Setup(const std::weak_ptr<RenderGraph> &graph) {
	this->graph_ = graph;
}

}