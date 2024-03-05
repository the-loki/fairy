#include <runtime/engine.h>
#include <taskflow/taskflow.hpp>

int main() {
	fairy::runtime::Engine engine;

	if (engine.Initialize()) {
		engine.Start();
	}

	return 0;

}


