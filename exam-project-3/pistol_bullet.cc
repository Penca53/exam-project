#include "pistol_bullet.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/resource_manager.h"
#include "engine/tilemap.h"
#include "tile_id.h"

namespace exam_project {

namespace {

bool DoesCollide(sf::Vector2f position, const ng::Tilemap& tilemap) {
  TileID id = tilemap.GetWorldTile(position).GetID();
  return id == TileID::kWall ||
         (id >= TileID::kWallTopLeft && id <= TileID::kWallBottomRight);
}

}  // namespace

PistolBullet::PistolBullet(ng::App* app, sf::Vector2f direction,
                           const ng::Tilemap* tilemap)
    : ng::Node(app),
      direction_(direction),
      tilemap_(tilemap),
      sprite_(
          GetApp()->GetResourceManager().LoadTexture("Sprites/bullet_2.png")) {
  sprite_.setOrigin({4, 4});
}

void PistolBullet::Update() {
  sf::Vector2f pos = GetGlobalTransform().getPosition();
  if (!tilemap_->IsWithinWorldBounds(pos)) {
    Destroy();
    return;
  }

  if (DoesCollide(pos, *tilemap_)) {
    Destroy();
    return;
  }

  static constexpr float kMovementSpeed = 4.F;
  Translate(direction_ * kMovementSpeed);
}

void PistolBullet::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
