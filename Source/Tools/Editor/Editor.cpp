#include <Runtime/Engine.h>



int main()
{
    fairy::runtime::Engine engine;
    auto config = fairy::runtime::InitEngineConfig();

    if (engine.init(config)) {
        engine.start_main_loop();
    }
}



