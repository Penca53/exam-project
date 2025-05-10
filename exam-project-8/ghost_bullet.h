#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class GhostBullet : public ng::Node {
 public:
  GhostBullet(ng::App* app, sf::Vector2f direction, const ng::Tilemap* tilemap);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Vector2f direction_;
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite sprite_;
  const ng::CircleCollider* collider_ = nullptr;
};

}  // namespace exam_project