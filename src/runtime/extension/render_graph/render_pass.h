//
// Created by loki on 2024/3/9.
//

#pragma once

#include <runtime/extension/render_graph/render_graph_node.h>

namespace fairy::runtime::render {

class RenderPass : public RenderGraphNode {
public:
	explicit RenderPass(const std::string_view &name);
};

}
