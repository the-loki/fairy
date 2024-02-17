#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_wgpu.h"
#include <cstdio>

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>

#endif

#include <GLFW/glfw3.h>
#include <glfw3webgpu.h>
#include <webgpu/webgpu.h>
#include <webgpu_extra.h>

// Global WebGPU required states

static WGPUDevice wgpu_device = nullptr;
static WGPUAdapter wgpu_adapter = nullptr;
static WGPUSurface wgpu_surface = nullptr;
static WGPUInstance wgpu_instance = nullptr;
static WGPUTextureFormat wgpu_preferred_fmt = WGPUTextureFormat_RGBA8Unorm;
static WGPUSwapChain wgpu_swap_chain = nullptr;
static int wgpu_swap_chain_width = 0;
static int wgpu_swap_chain_height = 0;

// Forward declarations
static void MainLoopStep(void *window);
static bool InitWebGpu(GLFWwindow *window);
static void PrintGlfwError(int error, const char *description);
static void PrintWebGpuError(WGPUErrorType error_type, const char *message,
                             void *);

// Main code
int main(int, char **) {
  glfwSetErrorCallback(PrintGlfwError);

  if (!glfwInit())
    return 1;

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window = glfwCreateWindow(
      1280, 720, "Dear ImGui GLFW+WebGPU example", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    return 1;
  }

  if (!InitWebGpu(window)) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }
  glfwShowWindow(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void) io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  io.IniFilename = nullptr;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOther(window, true);

#ifdef __EMSCRIPTEN__
  ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif

  ImGui_ImplWGPU_InitInfo init_info;
  init_info.Device = wgpu_device;
  init_info.NumFramesInFlight = 3;
  init_info.RenderTargetFormat = wgpu_preferred_fmt;
  init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;

  ImGui_ImplWGPU_Init(&init_info);

#ifndef IMGUI_DISABLE_FILE_FUNCTIONS
//	io.Fonts->AddFontFromFileTTF("fonts/msyh.ttc", 16.0f, nullptr,
//io.Fonts->GetGlyphRangesChineseFull());
#endif

#ifndef __EMSCRIPTEN__
  while (!glfwWindowShouldClose(window)) {
    MainLoopStep(window);
  }
#else
  emscripten_set_main_loop_arg(MainLoopStep, window, 0, false);
#endif

  return 0;
}

static bool InitWebGpu(GLFWwindow *window) {
  using namespace webgpu_extra;

#ifndef __EMSCRIPTEN__
  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;
  wgpu_instance = wgpuCreateInstance(&desc);
  wgpu_surface = glfwGetWGPUSurface(wgpu_instance, window);

  WGPURequestAdapterOptions adapter_opts = {};
  adapter_opts.nextInChain = nullptr;
  adapter_opts.compatibleSurface = wgpu_surface;
  wgpu_adapter = RequestAdapter(wgpu_instance, &adapter_opts);
  wgpu_preferred_fmt =
      wgpuSurfaceGetPreferredFormat(wgpu_surface, wgpu_adapter);

  WGPUDeviceDescriptor device_desc = {};
  device_desc.nextInChain = nullptr;
  device_desc.label = "My Device"; // anything works here, that's your call
  device_desc.requiredFeaturesCount = 0;                               // we do not require any specific feature
  device_desc.requiredLimits = nullptr; // we do not require any specific limit
  device_desc.defaultQueue.nextInChain = nullptr;
  device_desc.defaultQueue.label = "The default queue";

  wgpu_device = RequestDevice(wgpu_adapter, &device_desc);
#else
  wgpu_device = emscripten_webgpu_get_device();
  wgpu::SurfaceDescriptorFromCanvasHTMLSelector html_surface_desc = {};
  html_surface_desc.selector = "#canvas";
  WGPUSurfaceDescriptor surfaceDesc = {};
  surfaceDesc.nextInChain = (WGPUChainedStruct *)&html_surface_desc;

  wgpu_instance = wgpuCreateInstance(nullptr);
  wgpu_surface = wgpuInstanceCreateSurface(wgpu_instance, &surfaceDesc);
  wgpu_preferred_fmt = wgpuSurfaceGetPreferredFormat(wgpu_surface, nullptr);
#endif

  if (!wgpu_device)
    return false;

  wgpuDeviceSetUncapturedErrorCallback(wgpu_device, PrintWebGpuError, nullptr);

  return true;
}

static void MainLoopStep(void *window) {
  ImGuiIO &io = ImGui::GetIO();

  glfwPollEvents();

  int width, height;
  glfwGetFramebufferSize((GLFWwindow *) window, &width, &height);

  // React to changes in screen size
  if (width != wgpu_swap_chain_width && height != wgpu_swap_chain_height) {
    ImGui_ImplWGPU_InvalidateDeviceObjects();
    if (wgpu_swap_chain)
      wgpuSwapChainRelease(wgpu_swap_chain);
    wgpu_swap_chain_width = width;
    wgpu_swap_chain_height = height;
    WGPUSwapChainDescriptor swap_chain_desc = {};
    swap_chain_desc.usage = WGPUTextureUsage_RenderAttachment;
    swap_chain_desc.format = wgpu_preferred_fmt;
    swap_chain_desc.width = width;
    swap_chain_desc.height = height;
    swap_chain_desc.presentMode = WGPUPresentMode_Fifo;
    wgpu_swap_chain =
        wgpuDeviceCreateSwapChain(wgpu_device, wgpu_surface, &swap_chain_desc);
    ImGui_ImplWGPU_CreateDeviceObjects();
  }

  // Start the Dear ImGui frame
  ImGui_ImplWGPU_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Our state
  // (we use static, which essentially makes the variable globals, as a
  // convenience to keep the example code easy to follow)
  static bool show_demo_window = true;
  static bool show_another_window = false;
  static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to create a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and
    // append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use
    // a format strings too)
    ImGui::Checkbox(
        "Demo Window",
        &show_demo_window); // Edit bool storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(
        "clear color",
        (float *) &clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button")) // Buttons return true when clicked (most
      // widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
    // window will have a closing button that will
    // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  // Rendering
  ImGui::Render();

  WGPURenderPassColorAttachment color_attachments = {};
  color_attachments.loadOp = WGPULoadOp_Clear;
  color_attachments.storeOp = WGPUStoreOp_Store;
  color_attachments.clearValue = {clear_color.x * clear_color.w,
                                  clear_color.y * clear_color.w,
                                  clear_color.z * clear_color.w, clear_color.w};
  color_attachments.view = wgpuSwapChainGetCurrentTextureView(wgpu_swap_chain);
  WGPURenderPassDescriptor render_pass_desc = {};
  render_pass_desc.colorAttachmentCount = 1;
  render_pass_desc.colorAttachments = &color_attachments;
  render_pass_desc.depthStencilAttachment = nullptr;

  WGPUCommandEncoderDescriptor enc_desc = {};
  WGPUCommandEncoder encoder =
      wgpuDeviceCreateCommandEncoder(wgpu_device, &enc_desc);

  WGPURenderPassEncoder pass =
      wgpuCommandEncoderBeginRenderPass(encoder, &render_pass_desc);
  ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
  wgpuRenderPassEncoderEnd(pass);

  WGPUCommandBufferDescriptor cmd_buffer_desc = {};
  WGPUCommandBuffer cmd_buffer =
      wgpuCommandEncoderFinish(encoder, &cmd_buffer_desc);
  WGPUQueue queue = wgpuDeviceGetQueue(wgpu_device);
  wgpuQueueSubmit(queue, 1, &cmd_buffer);

#ifndef __EMSCRIPTEN__
  wgpuSwapChainPresent(wgpu_swap_chain);
#endif
}

static void PrintGlfwError(int error, const char *description) {
  printf("GLFW Error %d: %s\n", error, description);
}

static void PrintWebGpuError(WGPUErrorType error_type, const char *message, void *) {
  std::string_view error_type_lb;

  switch (error_type) {
    case WGPUErrorType_Validation:error_type_lb = "Validation";
      break;
    case WGPUErrorType_OutOfMemory:error_type_lb = "Out of memory";
      break;
    case WGPUErrorType_Unknown:error_type_lb = "Unknown";
      break;
    case WGPUErrorType_DeviceLost:error_type_lb = "Device lost";
      break;
    default:error_type_lb = "Unknown";
  }

  printf("%s error: %s\n", error_type_lb.data(), message);
}