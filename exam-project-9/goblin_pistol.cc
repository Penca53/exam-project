#include "goblin_pistol.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/resource_manager.h"
#include "engine/tilemap.h"
#include "goblin.h"
#include "goblin_pistol_bullet.h"

namespace exam_project {

GoblinPistol::GoblinPistol(ng::App* app, const Goblin* goblin,
                           const ng::Tilemap* tilemap)
    : ng::Node(app),
      goblin_(goblin),
      tilemap_(tilemap),
      arm_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Goblin/goblin_arm.png")),
      shoot_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Bullet_1.wav")),
      shoot_point_(&MakeChild<ng::Node>()) {
  arm_.setOrigin({4, 4});
  arm_.setScale({8, 8});
  SetLocalPosition({4 * 4, 0});

  shoot_point_->SetLocalPosition({10, 0});
}

void GoblinPistol::FlipY(bool is_flipped) {
  arm_.setScale({8.F, is_flipped ? -8.F : 8.F});
}

void GoblinPistol::Update() {
  if (goblin_->GetIsDead()) {
    return;
  }

  if (shoot_timer_ <= 0) {
    sf::Vector2f right(1, 0);
    auto& bullet = GetScene()->MakeChild<GoblinPistolBullet>(
        right.rotatedBy(GetGlobalTransform().getRotation()), tilemap_);
    bullet.SetLocalPosition(shoot_point_->GetGlobalTransform().getPosition());
    shoot_sound_.play();
    shoot_timer_ = 60;
  } else {
    --shoot_timer_;
  }
}

void GoblinPistol::Draw(sf::RenderTarget& target) {
  target.draw(arm_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
