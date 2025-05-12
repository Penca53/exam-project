#include "enemy_spawner.h"

#include <cstdint>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "engine/tilemap.h"
#include "game_manager.h"
#include "ghost.h"
#include "goblin.h"
#include "player.h"
#include "shooting_ghost.h"

namespace exam_project {

EnemySpawner::EnemySpawner(ng::App* app, Player* player,
                           const ng::Tilemap* tilemap,
                           GameManager* game_manager, EnemyType enemy_type,
                           uint32_t spawn_count)
    : ng::Node(app),
      player_(player),
      tilemap_(tilemap),
      game_manager_(game_manager),
      enemy_type_(enemy_type),
      spawn_count_(spawn_count) {}

void EnemySpawner::Update() {
  if (spawned_count_ >= spawn_count_) {
    return;
  }

  ++spawn_timer_;
  if (spawn_timer_ >= 60 * 2) {
    switch (enemy_type_) {
      case EnemyType::kGhost: {
        if (game_manager_->GetState() != GameManager::State::PLAY) {
          break;
        }

        auto& ghost = GetScene()->MakeChild<Ghost>(player_, tilemap_);
        ghost.SetLocalPosition(GetGlobalTransform().getPosition());
        ++spawned_count_;
        break;
      }

      case EnemyType::kShootingGhost: {
        if (game_manager_->GetState() != GameManager::State::PLAY) {
          break;
        }

        auto& shooting_ghost =
            GetScene()->MakeChild<ShootingGhost>(player_, tilemap_);
        shooting_ghost.SetLocalPosition(GetGlobalTransform().getPosition());
        ++spawned_count_;
        break;
      }

      case EnemyType::kGoblin: {
        if (game_manager_->GetState() != GameManager::State::BOSS) {
          break;
        }

        auto& goblin =
            GetScene()->MakeChild<Goblin>(player_, tilemap_, game_manager_);
        goblin.SetLocalPosition(GetGlobalTransform().getPosition());
        ++spawned_count_;
        break;
      }

      default:
        break;
    }

    spawn_timer_ = 0;

    if (spawned_count_ == spawn_count_) {
      game_manager_->CompleteSpawner();
      if (game_manager_->GetCompletedSpawners() == 4) {
        game_manager_->Boss();
      }
    }
  }
}

}  // namespace exam_project