//
// Created by loki on 2024/2/24.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <runtime/function/framework/ecs/common/component.h>

namespace fairy::runtime::function::framework {

struct TransformComponent : public Component {
	glm::dvec3 scale_;
	glm::dvec3 position_;
	glm::dquat rotation_;

	glm::dvec3 world_scale_;
	glm::dvec3 world_position_;
	glm::dquat world_rotation_;
};

}
