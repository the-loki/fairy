#include <runtime/engine.h>
#include <taskflow/taskflow.hpp>

int main() {
	fairy::runtime::Engine engine;
	auto config = fairy::runtime::InitEngineConfig();

	if (engine.Init(config)) {
		engine.StartMainLoop();
	}

	return 0;

}


