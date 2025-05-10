#include "ghost.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

#include "engine/app.h"
#include "engine/collider.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
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
          "Sprites/Ghost/ghost.png")),
      death_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Pop_1.wav")) {
  SetName("Ghost");
  sprite_.setOrigin({4, 4});
  sprite_.setScale({4, 4});
  collider_ = &MakeChild<ng::RectangleCollider>(sf::Vector2f(32, 32));
}

void Ghost::TakeDamage(float damage) {
  if (is_dead_) {
    return;
  }

  health_ -= damage;
  if (health_ <= 0) {
    is_dead_ = true;
    death_sound_.play();
  }
}

bool Ghost::GetIsDead() const {
  return is_dead_;
}

void Ghost::Update() {  // NOLINT
  if (is_dead_) {
    if (death_timer_ > 0) {
      sprite_.setColor(sf::Color(255, 255, 255, death_timer_ * 255 / 60));
      --death_timer_;
    } else {
      Destroy();
    }
    return;
  }

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

  if (attack_timer_ > 0) {
    --attack_timer_;
  }

  std::vector<const ng::Collider*> others =
      GetScene()->GetPhysics().Overlap(*collider_);
  for (const auto* other : others) {
    if (other->GetParent()->GetName() == "Player") {
      if (attack_timer_ == 0) {
        auto* player = dynamic_cast<Player*>(other->GetParent());
        player->TakeDamage(10);
        attack_timer_ = 60 * 2;
      }
    }
  }
}

void Ghost::Draw(sf::RenderTarget& target) {
  target.draw(sprite_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project