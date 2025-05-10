#include "player_weapon_holder.h"

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "pistol.h"
#include "player.h"

namespace exam_project {

PlayerWeaponHolder::PlayerWeaponHolder(ng::App* app, Player* player,
                                       const ng::Camera* camera,
                                       const ng::Tilemap* tilemap)
    : ng::Node(app),
      player_(player),
      pistol_(&MakeChild<Pistol>(this, tilemap)),
      camera_(camera) {
  SetLocalPosition({0, -2 * 4});
}

bool PlayerWeaponHolder::GetIsLargeBulletsEnabled() const {
  return is_large_bullets_enabled;
}

void PlayerWeaponHolder::SetIsLargeBulletsEnabled(bool enabled) {
  is_large_bullets_enabled = enabled;
}

void PlayerWeaponHolder::Update() {
  sf::Vector2i mouse_pos_screen = sf::Mouse::getPosition(GetApp()->GetWindow());
  sf::Vector2f mouse_pos_world = GetApp()->GetWindow().mapPixelToCoords(
      mouse_pos_screen, camera_->GetView());
  sf::Vector2f direction = mouse_pos_world - GetGlobalTransform().getPosition();

  sf::Angle angle = sf::radians(std::atan2(direction.y, direction.x));
  if (std::abs(angle.asDegrees()) > 90) {
    pistol_->FlipY(true);
    player_->FlipX(true);
  } else {
    pistol_->FlipY(false);
    player_->FlipX(false);
  }

  SetLocalRotation(angle);
}

}  // namespace exam_project
