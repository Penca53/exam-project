#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <random>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/tilemap.h"
#include "player.h"

namespace exam_project {

class ShootingGhost : public ng::Node {
 public:
  ShootingGhost(ng::App* app, Player* player, const ng::Tilemap* tilemap);
  void TakeDamage(float damage);
  bool GetIsDead() const;

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite sprite_;
  sf::Sound shoot_sound_;
  sf::Sound death_sound_;
  const ng::RectangleCollider* collider_ = nullptr;
  float health_ = 40;
  bool is_dead_ = false;
  int32_t melee_attack_timer_ = 0;
  int32_t shoot_attack_timer_ = 0;
  int32_t death_timer_ = 60 * 1;
  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> large_bullet_pickup_drop_;
};

}  // namespace exam_project