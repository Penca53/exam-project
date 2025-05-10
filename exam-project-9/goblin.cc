#include "goblin.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdint>
#include <vector>

#include "engine/app.h"
#include "engine/collider.h"
#include "engine/node.h"
#include "engine/rectangle_collider.h"
#include "engine/scene.h"
#include "engine/tilemap.h"
#include "game_manager.h"
#include "goblin_pistol_bullet.h"
#include "goblin_weapon_holder.h"
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

Goblin::Goblin(ng::App* app, Player* player, const ng::Tilemap* tilemap,
               GameManager* game_manager)
    : ng::Node(app),
      player_(player),
      tilemap_(tilemap),
      game_manager_(game_manager),
      head_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Goblin/goblin_head.png")),
      body_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Goblin/goblin_body.png")),
      spawn_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Goblin.wav")),
      death_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Pop_1.wav")) {
  SetName("Goblin");
  head_.setOrigin({4, 2});
  head_.setPosition({0, -4 * 8});
  head_.setScale({8, 8});
  body_.setOrigin({4, 2});
  body_.setScale({8, 8});

  MakeChild<GoblinWeaponHolder>(this, player_, tilemap_);
  collider_ = &MakeChild<ng::RectangleCollider>(sf::Vector2f(48, 48));
}

void Goblin::FlipX(bool is_flipped) {
  head_.setScale({is_flipped ? -8.F : 8.F, 8});
  body_.setScale({is_flipped ? -8.F : 8.F, 8});
}

void Goblin::TakeDamage(float damage) {
  if (is_dead_) {
    return;
  }

  health_ -= damage;
  if (health_ <= 0) {
    is_dead_ = true;
    death_sound_.play();
    player_->AddScore(500);
    game_manager_->Win();
  }
}

bool Goblin::GetIsDead() const {
  return is_dead_;
}

void Goblin::OnAdd() {
  spawn_sound_.setVolume(1500);
  spawn_sound_.play();
}

void Goblin::Update() {  // NOLINT
  if (is_dead_) {
    if (death_timer_ > 0) {
      head_.setColor(sf::Color(255, 255, 255, death_timer_ * 255 / 60));
      body_.setColor(sf::Color(255, 255, 255, death_timer_ * 255 / 60));
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
    static constexpr float kMovementSpeed = 0.5F;
    velocity = diff.normalized() * kMovementSpeed;
  }

  sf::Vector2f old_pos = GetGlobalTransform().getPosition();
  sf::Vector2f new_pos = old_pos + velocity;

  sf::Vector2f col_half_size = sf::Vector2f(32, 32) / 2.F;
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

  if (blast_timer_ > 0) {
    --blast_timer_;
  } else {
    static constexpr int32_t kBulletCount = 16;
    for (int32_t i = 0; i < kBulletCount; ++i) {
      sf::Angle angle =
          sf::degrees((static_cast<float>(i) * 360.F / kBulletCount));

      sf::Vector2f dir(1, 0);
      auto& bullet = GetScene()->MakeChild<GoblinPistolBullet>(
          dir.rotatedBy(angle), tilemap_);
      bullet.SetLocalPosition(GetGlobalTransform().getPosition());
    }
    blast_timer_ = 60 * 3;
  }

  if (attack_timer_ > 0) {
    --attack_timer_;
  }

  std::vector<const ng::Collider*> others =
      GetScene()->GetPhysics().Overlap(*collider_);
  for (const auto* other : others) {
    if (other->GetParent()->GetName() == "Player") {
      if (attack_timer_ == 0) {
        auto* player = dynamic_cast<Player*>(other->GetParent());
        player->TakeDamage(20);
        attack_timer_ = 60 * 3;
      }
    }
  }
}

void Goblin::Draw(sf::RenderTarget& target) {
  target.draw(head_, GetGlobalTransform().getTransform());
  target.draw(body_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project