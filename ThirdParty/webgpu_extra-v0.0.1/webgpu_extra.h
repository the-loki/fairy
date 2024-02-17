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
inline void Request(auto status, auto target, auto message, void *pUserData) {
  auto &user_data = *reinterpret_cast<UserData<T> *>(pUserData);

  if (status == SuccessfulValue) {
    user_data.target = target;
  } else {
    std::cout << "Request failed: " << message << std::endl;
  }

  user_data.request_ended = true;
}

WGPUAdapter RequestAdapter(WGPUInstance instance, WGPURequestAdapterOptions const *options) {
  UserData<WGPUAdapter> user_data;
  constexpr auto kSuccessVal = WGPURequestAdapterStatus_Success;
  wgpuInstanceRequestAdapter(instance, options, &Request<WGPUAdapter, kSuccessVal>, (void *) &user_data);

  assert(user_data.request_ended);
  return user_data.target;
}

WGPUDevice RequestDevice(WGPUAdapter adapter, WGPUDeviceDescriptor const *descriptor) {
  UserData<WGPUDevice> user_data;
  constexpr auto kSuccessVal = WGPURequestDeviceStatus_Success;
  wgpuAdapterRequestDevice(adapter, descriptor, &Request<WGPUDevice, kSuccessVal>, (void *) &user_data);
  assert(user_data.request_ended);

  return user_data.target;
}

}