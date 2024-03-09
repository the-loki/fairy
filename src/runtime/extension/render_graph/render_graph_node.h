//
// Created by loki on 2024/3/9.
//

#pragma once

#include <string>

namespace fairy::runtime::render {

class RenderGraphNode {
protected:
	std::string name_;
public:
	explicit RenderGraphNode(const std::string_view &name);
};

}
