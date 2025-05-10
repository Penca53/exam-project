#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/tilemap.h"
#include "game_manager.h"
#include "player_weapon_holder.h"
#include "ui_manager.h"

namespace exam_project {

class Player : public ng::Node {
 public:
  Player(ng::App* app, const ng::Tilemap* tilemap, const ng::Camera* camera,
         UIManager* ui_manager, GameManager* game_manager);
  void FlipX(bool is_flipped);
  void TakeDamage(float damage);
  void AddScore(int32_t score);
  void AddHealth(float health);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const ng::Tilemap* tilemap_ = nullptr;
  UIManager* ui_manager_ = nullptr;
  GameManager* game_manager_ = nullptr;
  sf::Sprite head_;
  sf::Sprite body_;
  sf::Sound hit_sound_;
  sf::Sound pickup_sound_;
  PlayerWeaponHolder* player_weapon_holder_ = nullptr;
  const ng::RectangleCollider* collider_ = nullptr;
  float health_ = 100;
  bool is_dead_ = false;
  int32_t score_ = 0;
  int32_t large_bullet_timer_ = 0;
};

}  // namespace exam_project