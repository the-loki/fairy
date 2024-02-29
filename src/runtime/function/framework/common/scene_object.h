//
// Created by loki on 2024/2/25.
//

#pragma once

#include <memory>
#include <runtime/core/common/type_traits.h>
#include "scene_object_id.h"

namespace fairy::runtime::function::framework {

class SceneObject : public core::NonCopyableAndMovable {
public:
	SceneObject() = default;
public:
	SceneObjectID parent_id_;
};

}
