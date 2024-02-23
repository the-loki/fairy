//
// Created by loki on 2024/2/17.
//

#pragma once

#include "render_graph_node.h"
#include "render_graph.h"
#include <memory>

namespace fairy::runtime::function::render {

class RenderPass : public RenderGraphNode {
public:
	explicit RenderPass(const std::string_view &name);
	~RenderPass() = default;

public:
	virtual void Execute() = 0;
	virtual void Setup(const std::weak_ptr<RenderGraph> &graph);
public:
	std::weak_ptr<RenderGraph> graph_;
};

}