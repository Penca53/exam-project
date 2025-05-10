#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "player.h"

namespace exam_project {

class HealthPickup : public ng::Node {
 public:
  explicit HealthPickup(ng::App* app);
  void Pickup(Player* player);

 protected:
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Sprite sprite_;
};

}  // namespace exam_project