//
// Created by loki on 24-4-21.
//

#include <runtime/render/renderable/renderable.h>

namespace fairy::runtime::render {

void Renderable::submit() {

}

Renderable::Renderable(const std::weak_ptr<Render> &render) : render_(render) {

}

}
