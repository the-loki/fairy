//
// Created by loki on 2024/2/23.
//


#pragma once

#include "runtime/function/render/render_pass.h"

namespace fairy::runtime::function::render {

class ForwardLightingPass : public RenderPass {
public:
	ForwardLightingPass();
	virtual ~ForwardLightingPass();
public:
	void Setup(const std::weak_ptr<RenderGraph> &graph) override;
	void Execute() override;
};

}