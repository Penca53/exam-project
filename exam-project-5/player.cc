#include "player.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/input.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/resource_manager.h"
#include "engine/tilemap.h"
#include "player_weapon_holder.h"
#include "tile_id.h"

namespace exam_project {

namespace {

bool DoesCollide(sf::Vector2f position, const ng::Tilemap& tilemap) {
  TileID id = tilemap.GetWorldTile(position).GetID();
  return id == TileID::kWall ||
         (id >= TileID::kWallTopLeft && id <= TileID::kWallBottomRight);
}

}  // namespace

Player::Player(ng::App* app, const ng::Tilemap* tilemap,
               const ng::Camera* camera)
    : ng::Node(app),
      tilemap_(tilemap),
      head_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Player/head.png")),
      body_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Player/body.png")) {
  SetName("Player");
  head_.setOrigin({4, 2});
  head_.setPosition({0, -4 * 4});
  body_.setOrigin({4, 2});

  head_.setScale({4, 4});
  body_.setScale({4, 4});

  MakeChild<PlayerWeaponHolder>(this, camera, tilemap_);
  collider_ = &MakeChild<ng::RectangleCollider>(sf::Vector2f(16, 16));
}

void Player::FlipX(bool is_flipped) {
  head_.setScale({is_flipped ? -4.F : 4.F, 4});
}

void Player::TakeDamage(float damage) {
  if (is_dead_) {
    return;
  }

  health_ -= damage;
  if (health_ <= 0) {
    is_dead_ = true;
    Destroy();
  }
}

void Player::Update() {  // NOLINT
  if (is_dead_) {
    return;
  }

  sf::Vector2f direction;
  const ng::Input& input = GetApp()->GetInput();
  if (input.GetKey(sf::Keyboard::Scancode::A)) {
    direction.x -= 1;
  }
  if (input.GetKey(sf::Keyboard::Scancode::D)) {
    direction.x += 1;
  }
  if (input.GetKey(sf::Keyboard::Scancode::W)) {
    direction.y -= 1;
  }
  if (input.GetKey(sf::Keyboard::Scancode::S)) {
    direction.y += 1;
  }

  sf::Vector2f velocity;
  if (direction.lengthSquared() > 0) {
    static constexpr float kMovementSpeed = 4.F;
    velocity = direction.normalized() * kMovementSpeed;
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

void Player::Draw(sf::RenderTarget& target) {
  target.draw(head_, GetGlobalTransform().getTransform());
  target.draw(body_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
