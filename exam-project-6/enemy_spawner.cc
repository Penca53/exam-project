#include "enemy_spawner.h"

#include <cstdint>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "engine/tilemap.h"
#include "ghost.h"
#include "player.h"
#include "shooting_ghost.h"

namespace exam_project {

EnemySpawner::EnemySpawner(ng::App* app, const Player* player,
                           const ng::Tilemap* tilemap, EnemyType enemy_type)
    : ng::Node(app),
      player_(player),
      tilemap_(tilemap),
      enemy_type_(enemy_type) {}

void EnemySpawner::Update() {
  static constexpr uint32_t kSpawnCount = 4;
  if (spawned_count_ >= kSpawnCount) {
    return;
  }

  ++spawn_timer_;
  if (spawn_timer_ >= 60 * 3) {
    switch (enemy_type_) {
      case EnemyType::kGhost: {
        auto& ghost = GetScene()->MakeChild<Ghost>(player_, tilemap_);
        ghost.SetLocalPosition(GetGlobalTransform().getPosition());
        break;
      }

      case EnemyType::kShootingGhost: {
        auto& shooting_ghost =
            GetScene()->MakeChild<ShootingGhost>(player_, tilemap_);
        shooting_ghost.SetLocalPosition(GetGlobalTransform().getPosition());
        break;
      }

      default:
        break;
    }

    spawn_timer_ = 0;
    ++spawned_count_;
  }
}

}  // namespace exam_project