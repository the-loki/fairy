//
// Created by loki on 2024/3/5.
//

#include <runtime/render/system/render_system.h>
#include <runtime/window/system/window_system.h>
#include <glfw3webgpu.h>
#include <webgpu_extra.h>
#include <runtime/render/utility.h>

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>

#endif

namespace fairy::runtime::render {

void RenderSystem::Initialize(flecs::world &world) {
	world.system<GraphicsContext, const Window>().kind(flecs::OnStart).each(RenderSystem::SetupGraphicsContext);
	world.system<GraphicsContext, const Window>().kind(flecs::PreUpdate).each(RenderSystem::SetupSwapChain);
}

void RenderSystem::SetupGraphicsContext(GraphicsContext &graphics_context, const Window &window) {
	using namespace webgpu_extra;

#ifndef __EMSCRIPTEN__
	WGPUInstanceDescriptor instance_desc = {};
	instance_desc.nextInChain = nullptr;
	graphics_context.instance_ = wgpuCreateInstance(&instance_desc);
	graphics_context.surface_ = glfwGetWGPUSurface(graphics_context.instance_, window.window_);

	WGPURequestAdapterOptions adapter_opts = {};
	adapter_opts.nextInChain = nullptr;
	adapter_opts.compatibleSurface = graphics_context.surface_;

#ifdef _WIN32
	adapter_opts.backendType = WGPUBackendType_D3D12;
#elif __APPLE__
	adapter_opts.backendType = WGPUBackendType_Metal;
#elif __linux__
	adapter_opts.backendType = WGPUBackendType_Vulkan;
#endif

	graphics_context.adapter_ = request_adapter(graphics_context.instance_, &adapter_opts);

	WGPUDeviceDescriptor device_desc = {};
	device_desc.nextInChain = nullptr;
	device_desc.label = "WebGPU Device";
	device_desc.requiredFeaturesCount = 0;
	device_desc.requiredLimits = nullptr;
	device_desc.defaultQueue.nextInChain = nullptr;
	device_desc.defaultQueue.label = "WebGPU Default Queue";
	graphics_context.device_ = request_device(graphics_context.adapter_, &device_desc);
#else
	this->device = emscripten_webgpu_get_device();
#endif

	if (!graphics_context.device_) {
		glfwSetWindowShouldClose(window.window_, GLFW_TRUE);
		return;
	}

	wgpuDeviceSetUncapturedErrorCallback(graphics_context.device_, &OutputWebGPUError, nullptr);

#ifdef __EMSCRIPTEN__
	WGPUSurfaceDescriptorFromCanvasHTMLSelector selector = {};
	selector.selector = "#canvas";
	selector.chain = {};
	selector.chain.next = nullptr;
	selector.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
	WGPUSurfaceDescriptor surface_desc = {};
	surface_desc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&selector);
	this->instance = wgpuCreateInstance(nullptr);
	this->surface = wgpuInstanceCreateSurface(graphics_context.instance, &surface_desc);
	this->texture_format = wgpuSurfaceGetPreferredFormat(graphics_context.surface, nullptr);
#endif

	graphics_context.supported_limits_.nextInChain = nullptr;
	wgpuDeviceGetLimits(graphics_context.device_, &(graphics_context.supported_limits_));
}

void RenderSystem::SetupSwapChain(GraphicsContext &graphics_context, const RenderSystem::Window &window) {
	if (window.size_.x!=graphics_context.swap_chain_size_.x || window.size_.y!=graphics_context.swap_chain_size_.y) {

	}
}

}
