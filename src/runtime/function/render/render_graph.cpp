//
// Created by loki on 2024/2/17.
//

#include "render_graph.h"

namespace fairy::runtime::function::render {

void RenderGraph::Setup(const std::shared_ptr<RenderPass> &pass) {
	passes_.push_back(pass);
	pass->Setup(shared_from_this());
}

void RenderGraph::Execute() {
	for (const auto &kPass : execution_flow_) {
		kPass->Execute();
	}
}

}