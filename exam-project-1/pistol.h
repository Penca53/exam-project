#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"

namespace exam_project {

class Pistol : public ng::Node {
 public:
  explicit Pistol(ng::App* app);
  void FlipY(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Sprite arm_;
};

}  // namespace exam_project