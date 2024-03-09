//
// Created by loki on 2024/3/9.
//

#include <runtime/extension/render_graph/render_graph_node.h>

#include <utility>

namespace fairy::runtime::render {

RenderGraphNode::RenderGraphNode(const std::string_view &name) : name_(name) {
}

}