//
// Created by loki on 2024/2/16.
//

#pragma once

#include <memory>
#include <Runtime/Platform/Window/Window.h>

namespace fairy::runtime {

struct InitEngineConfig {
  platform::InitWindowConfig window_config;
};

class Engine : public core::Object {
public:
    Engine() = default;
    ~Engine() override = default;

    virtual void start_main_loop();
    virtual bool init(const InitEngineConfig& config);

protected:
    [[nodiscard]] bool should_finish() const;
    void main_loop_step() const;

public:

    std::shared_ptr<platform::Window> window = nullptr;
};

}
