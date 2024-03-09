//
// Created by loki on 2024/3/9.
//

#include <runtime/extension/render_graph/render_pass.h>

namespace fairy::runtime::render {

RenderPass::RenderPass(const std::string_view &name) : RenderGraphNode(name) {
}

}