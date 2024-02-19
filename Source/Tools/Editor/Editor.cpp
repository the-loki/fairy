#include <Runtime/Engine.h>

int main()
{
	fairy::runtime::Engine engine;

	if (engine.init()) {
		engine.start_main_loop();
	}
}



