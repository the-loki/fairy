//
// Created by loki on 2024/2/17.
//

#pragma once

#include "render_pass.h"
#include "render_resource.h"
#include "runtime/core/common/object.h"
#include <memory>
#include <vector>

namespace fairy::runtime::function::render {

class RenderGraph : public core::Object {
public:
	RenderGraph() = default;
	~RenderGraph() override = default;

public:
	void addPass(const std::shared_ptr<RenderPass> &pass);
	void addResource(const std::shared_ptr<RenderResource> &resource);

public:
	std::vector<std::shared_ptr<RenderPass>> passes_;
	std::vector<std::shared_ptr<RenderResource>> resources_;
	std::vector<std::shared_ptr<RenderPass>> execution_flow_;
};

}
