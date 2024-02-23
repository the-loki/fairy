//
// Created by loki on 2024/2/17.
//

#pragma once

#include <string_view>

namespace fairy::runtime::function::render {

class RenderGraphNode {
public:
	explicit RenderGraphNode(const std::string_view& name);
public:
	std::string_view name_;
};

}
