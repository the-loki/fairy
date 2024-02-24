//
// Created by loki on 2024/2/23.
//

#pragma once

#include <runtime/core/common/object.h>
#include <runtime/core/common/non_copyable.h>

namespace fairy::runtime::function::ecs {

class System : public core::Object, core::NonCopyable {
	virtual void Tick(float delta_time) = 0;
	virtual void PhysTick(float delta_time) = 0;
};

}
