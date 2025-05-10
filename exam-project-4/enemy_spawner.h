#pragma once

#include <cstdint>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "player.h"

namespace exam_project {

class EnemySpawner : public ng::Node {
 public:
  EnemySpawner(ng::App* app, const Player* player, const ng::Tilemap* tilemap);

 protected:
  void Update() override;

 private:
  const Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  uint32_t spawn_timer_ = 0;
  uint32_t spawned_count_ = 0;
};

}  // namespace exam_project