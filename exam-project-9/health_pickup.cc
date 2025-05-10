#include "health_pickup.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "player.h"

namespace exam_project {

HealthPickup::HealthPickup(ng::App* app)
    : ng::Node(app),
      sprite_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/PickUp/heal_cross.png")) {
  SetName("HealthPickup");
  sprite_.setOrigin({4, 4});
  sprite_.setScale({4, 4});

  MakeChild<ng::RectangleCollider>(sf::Vector2f(32, 32));
}

void HealthPickup::Pickup(Player* player) {
  player->AddHealth(30);
  Destroy();
}

void HealthPickup::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
