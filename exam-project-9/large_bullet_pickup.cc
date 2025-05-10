#include "large_bullet_pickup.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"

namespace exam_project {

LargeBulletPickup::LargeBulletPickup(ng::App* app)
    : ng::Node(app),
      sprite_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/PickUp/powerup.png")) {
  SetName("LargeBulletPickup");
  sprite_.setOrigin({4, 4});
  sprite_.setScale({4, 4});

  MakeChild<ng::RectangleCollider>(sf::Vector2f(32, 32));
}

void LargeBulletPickup::Pickup() {
  Destroy();
}

void LargeBulletPickup::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
