#include "ghost.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/scene.h"
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

Ghost::Ghost(ng::App* app, const Player* player, const ng::Tilemap* tilemap)
    : ng::Node(app),
      player_(player),
      tilemap_(tilemap),
      sprite_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Ghost/ghost.png")) {
  sprite_.setOrigin({4, 4});
  sprite_.setScale({4, 4});
}

void Ghost::Update() {
  if (!GetScene()->IsValid(player_)) {
    return;
  }

  sf::Vector2f diff = (player_->GetGlobalTransform().getPosition() -
                       GetGlobalTransform().getPosition());
  sf::Vector2f velocity;
  if (diff.lengthSquared() > 0) {
    static constexpr float kMovementSpeed = 1.F;
    velocity = diff.normalized() * kMovementSpeed;
  }

  sf::Vector2f old_pos = GetGlobalTransform().getPosition();
  sf::Vector2f new_pos = old_pos + velocity;

  sf::Vector2f col_half_size = sf::Vector2f(16, 16) / 2.F;
  sf::Vector2f tilemap_size = sf::Vector2f(tilemap_->GetTileSize());

  static constexpr float kEps = 0.001F;
  sf::Vector2f top_left = {new_pos.x - (col_half_size.x - kEps),
                           old_pos.y - (col_half_size.y - kEps)};
  sf::Vector2f bottom_left = {new_pos.x - (col_half_size.x - kEps),
                              old_pos.y + (col_half_size.y - kEps)};

  if (!tilemap_->IsWithinWorldBounds(top_left) ||
      !tilemap_->IsWithinWorldBounds(bottom_left)) {
    return;
  }

  if (velocity.x < 0 && (DoesCollide(top_left, *tilemap_) ||
                         DoesCollide(bottom_left, *tilemap_))) {
    new_pos.x = std::ceil(top_left.x / tilemap_size.x) * tilemap_size.x +
                col_half_size.x;
    velocity.x = 0;
  }

  sf::Vector2f top_right = {new_pos.x + (col_half_size.x - kEps),
                            old_pos.y - (col_half_size.y - kEps)};
  sf::Vector2f bottom_right = {new_pos.x + (col_half_size.x - kEps),
                               old_pos.y + (col_half_size.y - kEps)};

  if (!tilemap_->IsWithinWorldBounds(top_right) ||
      !tilemap_->IsWithinWorldBounds(bottom_right)) {
    return;
  }

  if (velocity.x > 0 && (DoesCollide(top_right, *tilemap_) ||
                         DoesCollide(bottom_right, *tilemap_))) {
    new_pos.x = std::floor(top_right.x / tilemap_size.x) * tilemap_size.x -
                col_half_size.x;
    velocity.x = 0;
  }

  top_left = {new_pos.x - (col_half_size.x - kEps),
              new_pos.y - (col_half_size.y - kEps)};
  top_right = {new_pos.x + (col_half_size.x - kEps),
               new_pos.y - (col_half_size.y - kEps)};

  if (!tilemap_->IsWithinWorldBounds(top_left) ||
      !tilemap_->IsWithinWorldBounds(top_right)) {
    return;
  }

  if (velocity.y < 0 &&
      (DoesCollide(top_left, *tilemap_) || DoesCollide(top_right, *tilemap_))) {
    new_pos.y = std::ceil(top_left.y / tilemap_size.y) * tilemap_size.y +
                col_half_size.y;
    velocity.y = 0;
  }

  bottom_left = {new_pos.x - (col_half_size.x - kEps),
                 new_pos.y + (col_half_size.y - kEps)};
  bottom_right = {new_pos.x + (col_half_size.x - kEps),
                  new_pos.y + (col_half_size.y - kEps)};

  if (!tilemap_->IsWithinWorldBounds(bottom_left) ||
      !tilemap_->IsWithinWorldBounds(bottom_right)) {
    return;
  }

  if (velocity.y > 0 && (DoesCollide(bottom_left, *tilemap_) ||
                         DoesCollide(bottom_right, *tilemap_))) {
    new_pos.y = std::floor(bottom_left.y / tilemap_size.y) * tilemap_size.y -
                col_half_size.y;
    velocity.y = 0;
  }

  SetLocalPosition(new_pos);
}

void Ghost::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project