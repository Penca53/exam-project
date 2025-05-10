#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class PistolBullet : public ng::Node {
 public:
  PistolBullet(ng::App* app, sf::Vector2f direction,
               const ng::Tilemap* tilemap);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Vector2f direction_;
  const ng::Tilemap* tilemap_;
  sf::Sprite sprite_;
};

}  // namespace exam_project