//
// Created by loki on 2024/2/19.
//

#include <runtime/platform/Window.h>
#include <glfw3webgpu.h>
#include <webgpu_extra.h>

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>

#endif

namespace fairy::runtime::platform {

static void print_wgpu_error(WGPUErrorType error_type, const char *message, void *) {
	const char *error_type_lb;

	switch (error_type) {
		case WGPUErrorType_Validation: error_type_lb = "Validation";
			break;
		case WGPUErrorType_OutOfMemory: error_type_lb = "Out of memory";
			break;
		case WGPUErrorType_Unknown: error_type_lb = "Unknown";
			break;
		case WGPUErrorType_DeviceLost: error_type_lb = "Device lost";
			break;
		default: error_type_lb = "Unknown";
	}

	printf("%s error: %s\n", error_type_lb, message);
}

bool GraphicsContext::Init(GLFWwindow *window) {
	using namespace webgpu_extra;

#ifndef __EMSCRIPTEN__
	WGPUInstanceDescriptor instance_desc = {};
	instance_desc.nextInChain = nullptr;
	instance_ = wgpuCreateInstance(&instance_desc);
	surface_ = glfwGetWGPUSurface(instance_, window);

	WGPURequestAdapterOptions adapter_opts = {};
	adapter_opts.nextInChain = nullptr;
	adapter_opts.compatibleSurface = surface_;

#ifdef _WIN32
	adapter_opts.backendType = WGPUBackendType_D3D12;
#elif __APPLE__
	adapter_opts.backendType = WGPUBackendType_Metal;
#elif __linux__
	adapter_opts.backendType = WGPUBackendType_Vulkan;
#endif

	adapter_ = request_adapter(instance_, &adapter_opts);

	WGPUDeviceDescriptor device_desc = {};
	device_desc.nextInChain = nullptr;
	device_desc.label = "WebGPU Device";
	device_desc.requiredFeaturesCount = 0;
	device_desc.requiredLimits = nullptr;
	device_desc.defaultQueue.nextInChain = nullptr;
	device_desc.defaultQueue.label = "WebGPU Default Queue";
	device_ = request_device(adapter_, &device_desc);
#else
	this->device = emscripten_webgpu_get_device();
#endif

	if (!device_) {
		return false;
	}

	wgpuDeviceSetUncapturedErrorCallback(device_, &print_wgpu_error, nullptr);

#ifdef __EMSCRIPTEN__
	WGPUSurfaceDescriptorFromCanvasHTMLSelector selector = {};
	selector.selector = "#canvas";
	selector.chain = {};
	selector.chain.next = nullptr;
	selector.chain.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
	WGPUSurfaceDescriptor surface_desc = {};
	surface_desc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&selector);
	this->instance = wgpuCreateInstance(nullptr);
	this->surface = wgpuInstanceCreateSurface(this->instance, &surface_desc);
	this->texture_format = wgpuSurfaceGetPreferredFormat(this->surface, nullptr);
#endif

	return true;
}

GraphicsContext::~GraphicsContext() {
	if (swap_chain_) {
		wgpuSwapChainRelease(swap_chain_);
	}

	if (device_) {
		wgpuDeviceRelease(device_);
	}

	if (adapter_) {
		wgpuAdapterRelease(adapter_);
	}

	if (instance_) {
		wgpuInstanceRelease(instance_);
	}
}

}