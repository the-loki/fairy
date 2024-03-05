#include <runtime/engine.h>
#include <taskflow/taskflow.hpp>

struct Position {
	float x, y;
};

struct Velocity {
	float x, y;
};

int main() {
//	fairy::runtime::Engine engine;
//	auto config = fairy::runtime::InitEngineConfig();
//
//	if (engine.Init(config)) {
//		engine.Start();
//	}


	flecs::world ecs;
	ecs.set_threads(10);

	for (int i = 0; i < 10; ++i) {
		auto e = ecs.entity();
		e.set(Position{.x = 10, .y = 10});
	}

	ecs.system<Position>().multi_threaded().each([](flecs::entity e, Position& p) {
		std::cout << "System-001" << std::endl;
	});


	ecs.system<Position>().each([](flecs::entity e, Position& p) {
		std::cout << "System-002" << std::endl;
		e.world().quit();
	});

	while (ecs.progress());

	return 0;

}


