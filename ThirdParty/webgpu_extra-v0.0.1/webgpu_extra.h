#pragma once

#include <webgpu/webgpu.h>
#include <iostream>
#include <cassert>

namespace webgpu_extra {

template<typename T>
struct UserData {
  T target = nullptr;
  bool request_ended = false;
};

template<typename T, auto SuccessfulValue>
inline void request(auto status, auto target, auto message, void* pUserData)
{
	auto& user_data = *reinterpret_cast<UserData<T>*>(pUserData);

	if (status==SuccessfulValue) {
		user_data.target = target;
	}
	else {
		std::cout << "Request failed: " << message << std::endl;
	}

	user_data.request_ended = true;
}

inline WGPUAdapter request_adapter(WGPUInstance instance, WGPURequestAdapterOptions const* options)
{
	UserData<WGPUAdapter> user_data;
	constexpr auto k_success_val = WGPURequestAdapterStatus_Success;
	wgpuInstanceRequestAdapter(instance, options, &request<WGPUAdapter, k_success_val>, (void*)&user_data);

	assert(user_data.request_ended);
	return user_data.target;
}

inline WGPUDevice request_device(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor)
{
	UserData<WGPUDevice> user_data;
	constexpr auto k_success_val = WGPURequestDeviceStatus_Success;
	wgpuAdapterRequestDevice(adapter, descriptor, &request<WGPUDevice, k_success_val>, (void*)&user_data);
	assert(user_data.request_ended);

	return user_data.target;
}

}