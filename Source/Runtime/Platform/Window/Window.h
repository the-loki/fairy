//
// Created by loki on 2024/2/18.
//

#pragma once

#include <Runtime/Core/Math/Math.hpp>
#include <Runtime/Core/Common/Object.h>
#include <Runtime/Platform/Window/GraphicsContext.h>
#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <string_view>
#include <memory>

namespace fairy::runtime::platform {

struct InitWindowConfig {
  bool resizable = false;
  std::string_view title;
  core::math::ivec2 size{};

  InitWindowConfig()
          :resizable(false), title("Fairy"), size{1280, 720} { }
};

class Window : public core::Object {
public:
    Window() = default;
    ~Window() override;

    virtual bool open();
    virtual bool init_webgpu();
    virtual void init(const InitWindowConfig& config);

    static void poll_events();
    void get_framebuffer_size();
    [[nodiscard]] bool should_close() const;

public:
    std::string title;
    core::math::ivec2 size{};
    GLFWwindow* window = nullptr;
    std::shared_ptr<GraphicsContext> graphics_context = nullptr;
};

}

