//
// Created by loki on 2024/3/9.
//


#include <runtime/render/component/graphics_context.h>
#include <runtime/window/component/window.h>

using Window = fairy::runtime::window::Window;

namespace fairy::runtime::render {

void SetupSwapChain(GraphicsContext &ctx, const Window &window) {
	if (window.size_.x==ctx.swap_chain_size_.x && window.size_.y==ctx.swap_chain_size_.y) {
		return;
	}

	if (ctx.swap_chain_) {
		wgpuSwapChainRelease(ctx.swap_chain_);
		ctx.swap_chain_ = nullptr;
	}

	ctx.swap_chain_size_ = window.size_;

	if(window.size_.x == 0 || window.size_.y == 0){
		return;
	}

	auto swap_chain_desc = WGPUSwapChainDescriptor{};
	swap_chain_desc.width = window.size_.x;
	swap_chain_desc.height = window.size_.y;
	swap_chain_desc.presentMode = WGPUPresentMode_Fifo;
	swap_chain_desc.format = ctx.preferred_texture_format_;
	swap_chain_desc.usage = WGPUTextureUsage_RenderAttachment;
	ctx.swap_chain_ = wgpuDeviceCreateSwapChain(ctx.device_, ctx.surface_, &swap_chain_desc);
}

}