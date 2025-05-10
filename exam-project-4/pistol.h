#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class Pistol : public ng::Node {
 public:
  Pistol(ng::App* app, const ng::Tilemap* tilemap);
  void FlipY(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite arm_;
  ng::Node* shoot_point_ = nullptr;
};

}  // namespace exam_project