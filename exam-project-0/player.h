#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"

namespace exam_project {

class Player : public ng::Node {
 public:
  explicit Player(ng::App* app);
  void FlipX(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Sprite head_;
  sf::Sprite body_;
};

}  // namespace exam_project