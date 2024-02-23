//
// Created by loki on 2024/2/17.
//

#include "render_graph.h"

namespace fairy::runtime::function::render {

void RenderGraph::addPass(const std::shared_ptr<RenderPass> &pass) {
	passes_.push_back(pass);
}
void RenderGraph::addResource(const std::shared_ptr<RenderResource> &resource) {
	resources_.push_back(resource);
}


}