//
// Created by loki on 2024/3/9.
//

#pragma once

#include <runtime/extension/render_graph/render_graph_node.h>

namespace fairy::runtime::render {

class RenderResource : public RenderGraphNode{
public:
	explicit RenderResource(const std::string_view &name);
};

}
