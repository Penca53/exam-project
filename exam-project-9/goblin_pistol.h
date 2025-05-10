#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class Goblin;

class GoblinPistol : public ng::Node {
 public:
  GoblinPistol(ng::App* app, const Goblin* goblin, const ng::Tilemap* tilemap);
  void FlipY(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const Goblin* goblin_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite arm_;
  sf::Sound shoot_sound_;
  ng::Node* shoot_point_ = nullptr;
  int32_t shoot_timer_ = 60;
};

}  // namespace exam_project