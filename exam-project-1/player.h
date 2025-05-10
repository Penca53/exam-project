#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class Player : public ng::Node {
 public:
  Player(ng::App* app, const ng::Tilemap* tilemap);
  void FlipX(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite head_;
  sf::Sprite body_;
};

}  // namespace exam_project