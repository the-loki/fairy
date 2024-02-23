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

class RenderGraph : std::enable_shared_from_this<RenderGraph> {
public:
	RenderGraph() = default;
	~RenderGraph() = default;

public:
	void Setup(const std::shared_ptr<RenderPass> &pass);

	template<typename T>
	requires std::derived_from<T, RenderResource>
	void DeclareInputResourceSource(const std::shared_ptr<RenderPass> &pass);

	template<typename T>
	requires std::derived_from<T, RenderResource>
	void DeclareOutputResourceSource(const std::shared_ptr<RenderPass> &pass);

	void Execute();
public:
	std::vector<size_t> execution_flow_;
	std::vector<std::shared_ptr<RenderPass>> passes_;
	std::vector<std::shared_ptr<RenderResource>> resources_;
};

template<typename T>
requires std::derived_from<T, RenderResource>
void RenderGraph::DeclareInputResourceSource(const std::shared_ptr<RenderPass> &pass) {

}

template<typename T>
requires std::derived_from<T, RenderResource>
void RenderGraph::DeclareOutputResourceSource(const std::shared_ptr<RenderPass> &pass) {

}

}
