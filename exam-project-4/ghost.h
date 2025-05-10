#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "player.h"

namespace exam_project {

class Ghost : public ng::Node {
 public:
  Ghost(ng::App* app, const Player* player, const ng::Tilemap* tilemap);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const Player* player_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  sf::Sprite sprite_;
};

}  // namespace exam_project