#include <runtime/engine.h>
#include <taskflow/taskflow.hpp>

int main() {
	fairy::runtime::Engine engine;

	if (engine.Init()) {
		engine.Start();
	}

	return 0;

}


