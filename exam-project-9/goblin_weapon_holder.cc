#include "goblin_weapon_holder.h"

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "goblin.h"
#include "goblin_pistol.h"
#include "player.h"

namespace exam_project {

GoblinWeaponHolder::GoblinWeaponHolder(ng::App* app, Goblin* goblin,
                                       Player* player,
                                       const ng::Tilemap* tilemap)
    : ng::Node(app),
      goblin_(goblin),
      player_(player),
      goblin_pistol_(&MakeChild<GoblinPistol>(goblin, tilemap)) {
  SetLocalPosition({0, -2 * 8});
}

void GoblinWeaponHolder::Update() {
  if (goblin_->GetIsDead()) {
    return;
  }

  if (!GetScene()->IsValid(player_)) {
    return;
  }

  sf::Vector2f player_pos = player_->GetGlobalTransform().getPosition();
  sf::Vector2f direction = player_pos - GetGlobalTransform().getPosition();

  sf::Angle angle = sf::radians(std::atan2(direction.y, direction.x));
  if (std::abs(angle.asDegrees()) > 90) {
    goblin_pistol_->FlipY(true);
    goblin_->FlipX(true);
  } else {
    goblin_pistol_->FlipY(false);
    goblin_->FlipX(false);
  }

  SetLocalRotation(angle);
}

}  // namespace exam_project
