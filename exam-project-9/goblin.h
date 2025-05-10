#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/tilemap.h"
#include "game_manager.h"
#include "player.h"

namespace exam_project {

class Goblin : public ng::Node {
 public:
  Goblin(ng::App* app, Player* player, const ng::Tilemap* tilemap,
         GameManager* game_manager);
  void FlipX(bool is_flipped);
  void TakeDamage(float damage);
  bool GetIsDead() const;

 protected:
  void OnAdd() override;
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  GameManager* game_manager_ = nullptr;
  sf::Sprite head_;
  sf::Sprite body_;
  sf::Sound spawn_sound_;
  sf::Sound death_sound_;
  const ng::RectangleCollider* collider_ = nullptr;
  float health_ = 1500;
  bool is_dead_ = false;
  int32_t attack_timer_ = 0;
  int32_t blast_timer_ = 0;
  int32_t death_timer_ = 60;
};

}  // namespace exam_project