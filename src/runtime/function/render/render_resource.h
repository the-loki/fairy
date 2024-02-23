//
// Created by loki on 2024/2/20.
//


#pragma once

#include "render_graph_node.h"
#include <webgpu/webgpu.h>

namespace fairy::runtime::function::render {

class RenderResource : public RenderGraphNode {
public:
	explicit RenderResource(const std::string_view &name);
	~RenderResource() = default;
};

}
