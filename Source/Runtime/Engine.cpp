//
// Created by loki on 2024/2/16.
//

#include "Engine.h"

namespace fairy::runtime {

bool Engine::init(const InitEngineConfig& config)
{
    window = std::make_shared<platform::Window>();
    window->init(config.window_config);

    if (!window->open()) {
        window.reset();
        return false;
    }

    return true;
}

void Engine::start_main_loop()
{
#ifndef __EMSCRIPTEN__
    while (!should_finish()) {
        main_loop_step();
    }
#else
    emscripten_set_main_loop_arg(main_loop_step, window, 0, false);
#endif
}

bool Engine::should_finish() const
{
    return window->should_close();
}

void Engine::main_loop_step() const
{
    window->poll_events();
    window->get_framebuffer_size();
    const auto frame_buffer_size = window->size;
}

}
