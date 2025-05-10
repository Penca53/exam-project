#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cstdint>

#include "engine/node.h"

namespace exam_project {

class UIManager : public ng::Node {
 public:
  explicit UIManager(ng::App* app);

  void UpdateScore(int32_t score);
  void UpdateHealth(float health);

 protected:
  void Draw(sf::RenderTarget& target) override;

 private:
  sf::Text score_text_;
  sf::Text health_text_;
};

}  // namespace exam_project