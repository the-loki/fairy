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

class NonMovable {
public:
	NonMovable() = default;
	~NonMovable() = default;
	NonMovable(NonMovable &&) = delete;
	NonMovable &operator=(NonMovable &&) = delete;
};

class NonCopyableAndMovable {
public:
	NonCopyableAndMovable() = default;
	~NonCopyableAndMovable() = default;
	NonCopyableAndMovable(const NonCopyableAndMovable &) = delete;
	NonCopyableAndMovable &operator=(const NonCopyableAndMovable &) = delete;
	NonCopyableAndMovable(NonCopyableAndMovable &&) = default;
	NonCopyableAndMovable &operator=(NonCopyableAndMovable &&) = default;
};

}
