#include <runtime/engine.h>

int main() {
	fairy::runtime::Engine engine;
	auto config = fairy::runtime::InitEngineConfig();

	if (engine.Init(config)) {
		engine.StartMainLoop();
	}
}


