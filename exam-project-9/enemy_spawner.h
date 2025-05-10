#pragma once

#include <cstdint>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "game_manager.h"
#include "player.h"

namespace exam_project {

class EnemySpawner : public ng::Node {
 public:
  enum class EnemyType : uint32_t {  // NOLINT
    kGhost,
    kShootingGhost,
    kGoblin,
  };
  EnemySpawner(ng::App* app, Player* player, const ng::Tilemap* tilemap,
               GameManager* game_manager, EnemyType enemy_type,
               uint32_t spawn_count);

 protected:
  void Update() override;

 private:
  Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  GameManager* game_manager_ = nullptr;
  EnemyType enemy_type_{};
  uint32_t spawn_timer_ = 0;
  uint32_t spawn_count_ = 0;
  uint32_t spawned_count_ = 0;
};

}  // namespace exam_project