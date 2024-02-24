//
// Created by loki on 2024/2/24.
//

#pragma once

namespace fairy::runtime::core {

class NonCopyable {
public:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable &) = delete;
	NonCopyable &operator=(const NonCopyable &) = delete;
};

}
