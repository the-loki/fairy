//
// Created by loki on 2024/2/16.
//

#pragma once

namespace fairy::runtime::platform {

enum class SurfaceType {
  Windowed = 0,
  Fullscreen = 1,
  WindowedFullscreen = 2,
};

class Surface {
public:
  Surface() = default;
public:
  SurfaceType type;
};

}
