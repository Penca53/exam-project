#include "ui_manager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cstdint>
#include <format>

#include "engine/app.h"
#include "engine/layer.h"
#include "engine/node.h"

namespace exam_project {

UIManager::UIManager(ng::App* app)
    : ng::Node(app),
      score_text_(
          GetApp()->GetResourceManager().LoadFont("Roboto-Regular.ttf")),
      health_text_(
          GetApp()->GetResourceManager().LoadFont("Roboto-Regular.ttf")) {
  SetLayer(ng::Layer::kUI);
}

void UIManager::UpdateScore(int32_t score) {
  score_text_.setString(std::format("Score: {}", score));
  score_text_.setOrigin(score_text_.getGlobalBounds().size / 2.F);

  float height = static_cast<float>(GetApp()->GetWindow().getSize().y);
  score_text_.setPosition(sf::Vector2f(0, (-height / 2.F) + 16));
}

void UIManager::UpdateHealth(float health) {
  health_text_.setString(std::format("HP: {:.0f}", std::max(health, 0.F)));
  health_text_.setOrigin(health_text_.getGlobalBounds().size / 2.F);

  float height = static_cast<float>(GetApp()->GetWindow().getSize().y);
  health_text_.setPosition(sf::Vector2f(0, (height / 2.F) - 32));
}

void UIManager::Draw(sf::RenderTarget& target) {
  target.draw(score_text_, GetGlobalTransform().getTransform());
  target.draw(health_text_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project