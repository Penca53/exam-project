#include "pistol.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/resource_manager.h"

namespace exam_project {

Pistol::Pistol(ng::App* app)
    : ng::Node(app),
      arm_(
          GetApp()->GetResourceManager().LoadTexture("Sprites/Player/arm.png")),
      shoot_point_(&MakeChild<ng::Node>()) {
  arm_.setOrigin({4, 4});
  arm_.setScale({4, 4});
  SetLocalPosition({4 * 4, 0});

  shoot_point_->SetLocalPosition({10, 0});
}

void Pistol::FlipY(bool is_flipped) {
  arm_.setScale({4.F, is_flipped ? -4.F : 4.F});
}

void Pistol::Update() {}

void Pistol::Draw(sf::RenderTarget& target) {
  target.draw(arm_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
