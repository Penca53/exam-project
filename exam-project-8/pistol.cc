#include "pistol.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/resource_manager.h"
#include "engine/tilemap.h"
#include "pistol_bullet.h"
#include "player_weapon_holder.h"

namespace exam_project {

Pistol::Pistol(ng::App* app, const PlayerWeaponHolder* player_weapon_holder,
               const ng::Tilemap* tilemap)
    : ng::Node(app),
      player_weapon_holder_(player_weapon_holder),
      tilemap_(tilemap),
      arm_(
          GetApp()->GetResourceManager().LoadTexture("Sprites/Player/arm.png")),
      shoot_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Bullet_1.wav")),
      shoot_point_(&MakeChild<ng::Node>()) {
  arm_.setOrigin({4, 4});
  arm_.setScale({4, 4});
  SetLocalPosition({4 * 4, 0});

  shoot_point_->SetLocalPosition({10, 0});
}

void Pistol::FlipY(bool is_flipped) {
  arm_.setScale({4.F, is_flipped ? -4.F : 4.F});
}

void Pistol::Update() {
  if (GetApp()->GetInput().GetKeyDown(sf::Keyboard::Scancode::Space)) {
    sf::Vector2f right(1, 0);
    auto& bullet = GetScene()->MakeChild<PistolBullet>(
        right.rotatedBy(GetGlobalTransform().getRotation()), tilemap_);
    bullet.SetLocalPosition(shoot_point_->GetGlobalTransform().getPosition());
    bullet.SetLocalRotation(GetGlobalTransform().getRotation() +
                            sf::degrees(90));
    if (player_weapon_holder_->GetIsLargeBulletsEnabled()) {
      bullet.SetLocalScale({4, 4});
    }
    shoot_sound_.play();
  }
}

void Pistol::Draw(sf::RenderTarget& target) {
  target.draw(arm_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
