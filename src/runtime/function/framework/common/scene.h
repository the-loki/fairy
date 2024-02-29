//
// Created by loki on 2024/2/24.
//

#pragma once

#include <runtime/core/common/type_traits.h>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>

#include "scene_object.h"

namespace fairy::runtime::function::framework {

class Scene : public core::NonCopyableAndMovable {
public:
	explicit Scene(const std::string_view &name);
	~Scene() = default;
public:
	std::string name_;
	std::unordered_map<std::size_t, std::shared_ptr<SceneObject>> scene_objects_;
};

}
