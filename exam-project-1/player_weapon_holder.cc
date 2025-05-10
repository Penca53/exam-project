#include "player_weapon_holder.h"

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

#include "engine/app.h"
#include "engine/node.h"
#include "pistol.h"
#include "player.h"

namespace exam_project {

PlayerWeaponHolder::PlayerWeaponHolder(ng::App* app, Player* player)
    : ng::Node(app), player_(player), pistol_(&MakeChild<Pistol>()) {
  SetLocalPosition({0, -2 * 4});
}

void PlayerWeaponHolder::Update() {
  sf::Vector2i mouse_pos_screen = sf::Mouse::getPosition(GetApp()->GetWindow());
  sf::Vector2f mouse_pos_world =
      GetApp()->GetWindow().mapPixelToCoords(mouse_pos_screen);
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
