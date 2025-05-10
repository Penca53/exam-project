#include "default_scene.h"

#include <cstdint>
#include <memory>

#include "enemy_spawner.h"
#include "engine/app.h"
#include "engine/camera.h"
#include "engine/layer.h"
#include "engine/scene.h"
#include "engine/tile.h"
#include "engine/tilemap.h"
#include "engine/tileset.h"
#include "follow_player.h"
#include "game_manager.h"
#include "player.h"
#include "tile_id.h"
#include "ui_manager.h"

namespace exam_project {

std::unique_ptr<ng::Scene> MakeDefaultScene(ng::App* app) {
  auto scene = std::make_unique<ng::Scene>(app);
  scene->SetName("Scene");

  ng::Tileset tileset(
      {32, 32}, &app->GetResourceManager().LoadTexture("Sprites/tileset.png"));

  {
    tileset.AddTile(ng::Tile(TileID::kVoid));

    tileset.AddTile(
        ng::Tile(TileID::kWallTopLeft, sf::IntRect({0 * 8, 0 * 8}, {8, 8})));
    tileset.AddTile(
        ng::Tile(TileID::kWallTopCenter, sf::IntRect({1 * 8, 0 * 8}, {8, 8})));
    tileset.AddTile(
        ng::Tile(TileID::kWallTopRight, sf::IntRect({2 * 8, 0 * 8}, {8, 8})));
    tileset.AddTile(
        ng::Tile(TileID::kWallMiddleLeft, sf::IntRect({0 * 8, 1 * 8}, {8, 8})));
    tileset.AddTile(ng::Tile(TileID::kWallMiddleRight,
                             sf::IntRect({2 * 8, 1 * 8}, {8, 8})));
    tileset.AddTile(
        ng::Tile(TileID::kWallBottomLeft, sf::IntRect({0 * 8, 2 * 8}, {8, 8})));
    tileset.AddTile(ng::Tile(TileID::kWallBottomCenter,
                             sf::IntRect({1 * 8, 2 * 8}, {8, 8})));
    tileset.AddTile(ng::Tile(TileID::kWallBottomRight,
                             sf::IntRect({2 * 8, 2 * 8}, {8, 8})));

    tileset.AddTile(
        ng::Tile(TileID::kWall, sf::IntRect({3 * 8, 0 * 8}, {8, 8})));
    tileset.AddTile(
        ng::Tile(TileID::kGround, sf::IntRect({3 * 8, 1 * 8}, {8, 8})));
  }

  auto& tilemap_ground =
      scene->MakeChild<ng::Tilemap>(sf::Vector2u(64, 64), tileset);
  tilemap_ground.SetLocalPosition({-32 * 32, -32 * 32});

  for (uint32_t y = 32 - 10; y < 32 + 10; ++y) {
    for (uint32_t x = 32 - 13; x < 32 + 13; ++x) {
      tilemap_ground.SetTile({x, y}, TileID::kGround);
    }
  }

  auto& tilemap_walls =
      scene->MakeChild<ng::Tilemap>(sf::Vector2u(64, 64), tileset);
  tilemap_walls.SetLocalPosition({-32 * 32, -32 * 32});
  for (uint32_t y = 0; y < 64; ++y) {
    for (uint32_t x = 0; x < 64; ++x) {
      if ((x >= 32 - 13 && x <= 32 + 13 - 1) &&
          (y >= 32 - 10 && y <= 32 + 10 - 1)) {
        continue;
      }
      tilemap_walls.SetTile({x, y}, TileID::kWall);
    }
  }

  tilemap_walls.SetTile({32 - 13, 32 - 10}, TileID::kWallTopLeft);
  for (uint32_t x = 32 - 13 + 1; x < 32 + 13 - 1; ++x) {
    tilemap_walls.SetTile({x, 32 - 10}, TileID::kWallTopCenter);
  }
  tilemap_walls.SetTile({32 + 13 - 1, 32 - 10}, TileID::kWallTopRight);

  for (uint32_t y = 32 - 10 + 1; y < 32 + 10 - 1; ++y) {
    tilemap_walls.SetTile({32 - 13, y}, TileID::kWallMiddleLeft);
    tilemap_walls.SetTile({32 + 13 - 1, y}, TileID::kWallMiddleRight);
  }

  tilemap_walls.SetTile({32 - 13, 32 + 10 - 1}, TileID::kWallBottomLeft);
  for (uint32_t x = 32 - 13 + 1; x < 32 + 13 - 1; ++x) {
    tilemap_walls.SetTile({x, 32 + 10 - 1}, TileID::kWallBottomCenter);
  }
  tilemap_walls.SetTile({32 + 13 - 1, 32 + 10 - 1}, TileID::kWallBottomRight);

  auto& camera = scene->MakeChild<ng::Camera>();
  scene->MakeChild<ng::Camera>(1, ng::Layer::kUI);

  auto& ui_manager = scene->MakeChild<UIManager>();
  auto& game_manager = scene->MakeChild<GameManager>();

  auto& player = scene->MakeChild<Player>(&tilemap_walls, &camera, &ui_manager,
                                          &game_manager);
  camera.MakeChild<FollowPlayer>(&player);

  auto& spawner_0 =
      scene->MakeChild<EnemySpawner>(&player, &tilemap_walls, &game_manager,
                                     EnemySpawner::EnemyType::kGhost, 5);
  spawner_0.SetLocalPosition({-200, -200});

  auto& spawner_1 = scene->MakeChild<EnemySpawner>(
      &player, &tilemap_walls, &game_manager,
      EnemySpawner::EnemyType::kShootingGhost, 5);
  spawner_1.SetLocalPosition({200, -200});

  auto& spawner_2 = scene->MakeChild<EnemySpawner>(
      &player, &tilemap_walls, &game_manager,
      EnemySpawner::EnemyType::kShootingGhost, 5);
  spawner_2.SetLocalPosition({-200, 200});

  auto& spawner_3 =
      scene->MakeChild<EnemySpawner>(&player, &tilemap_walls, &game_manager,
                                     EnemySpawner::EnemyType::kGhost, 5);
  spawner_3.SetLocalPosition({200, 200});

  auto& boss_spawner =
      scene->MakeChild<EnemySpawner>(&player, &tilemap_walls, &game_manager,
                                     EnemySpawner::EnemyType::kGoblin, 1);
  boss_spawner.SetLocalPosition({0, 0});
  return scene;
}

}  // namespace exam_project