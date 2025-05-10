#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/tilemap.h"
#include "player.h"

namespace exam_project {

class Ghost : public ng::Node {
 public:
  Ghost(ng::App* app, const Player* player, const ng::Tilemap* tilemap);
  void TakeDamage(float damage);
  bool GetIsDead() const;

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite sprite_;
  sf::Sound death_sound_;
  const ng::RectangleCollider* collider_ = nullptr;
  float health_ = 50;
  bool is_dead_ = false;
  int32_t attack_timer_ = 0;
  int32_t death_timer_ = 60;
};

}  // namespace exam_project