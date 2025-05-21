#include "goblin_pistol_bullet.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "engine/app.h"
#include "engine/circle_collider.h"
#include "engine/collider.h"
#include "engine/node.h"
#include "engine/resource_manager.h"
#include "engine/tilemap.h"
#include "player.h"
#include "tile_id.h"

namespace exam_project {

namespace {

bool DoesCollide(sf::Vector2f position, const ng::Tilemap& tilemap) {
  TileID id = tilemap.GetWorldTile(position).GetID();
  return id == TileID::kWall ||
         (id >= TileID::kWallTopLeft && id <= TileID::kWallBottomRight);
}

}  // namespace

GoblinPistolBullet::GoblinPistolBullet(ng::App* app, sf::Vector2f direction,
                                       const ng::Tilemap* tilemap)
    : ng::Node(app),
      direction_(direction),
      tilemap_(tilemap),
      sprite_(
          GetApp()->GetResourceManager().LoadTexture("Sprites/bullet.png")) {
  sprite_.setOrigin({4, 4});
  sprite_.setScale({4, 4});
  sprite_.setColor(sf::Color::Green);
  collider_ = &MakeChild<ng::CircleCollider>(6.F);
}

void GoblinPistolBullet::Update() {
  sf::Vector2f pos = GetGlobalTransform().getPosition();
  if (!tilemap_->IsWithinWorldBounds(pos)) {
    Destroy();
    return;
  }

  if (DoesCollide(pos, *tilemap_)) {
    Destroy();
    return;
  }

  static constexpr float kMovementSpeed = 6.F;
  Translate(direction_ * kMovementSpeed);

  std::vector<const ng::Collider*> others =
      GetScene()->GetPhysics().Overlap(*collider_);
  for (const auto* other : others) {
    if (other->GetParent()->GetName() == "Player") {
      auto* player = dynamic_cast<Player*>(other->GetParent());
      player->TakeDamage(20);
      Destroy();
    }
  }
}

void GoblinPistolBullet::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
