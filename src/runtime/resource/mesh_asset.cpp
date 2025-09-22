//
// Created by loki on 24-4-26.
//

#include <runtime/resource/mesh_asset.h>
#include <runtime/core/lru.hpp>

namespace nyx::runtime::resource {

bool MeshAsset::load(const std::string &path) {
	using namespace nyx::runtime::core;
	auto cache = LRUCache<std::string, std::string>::getInstance();

	return true;
}

}
