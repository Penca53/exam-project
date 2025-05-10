#pragma once

#include <cstdint>

enum class TileID : uint64_t {  // NOLINT
  kVoid = 0,
  kWallTopLeft,
  kWallTopCenter,
  kWallTopRight,
  kWallMiddleLeft,
  kWallMiddleRight,
  kWallBottomLeft,
  kWallBottomCenter,
  kWallBottomRight,
  kWall,
  kGround,
};
