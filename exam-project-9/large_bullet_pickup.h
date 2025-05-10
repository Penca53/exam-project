#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"

namespace exam_project {

class LargeBulletPickup : public ng::Node {
 public:
  explicit LargeBulletPickup(ng::App* app);
  void Pickup();

 protected:
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Sprite sprite_;
};

}  // namespace exam_project