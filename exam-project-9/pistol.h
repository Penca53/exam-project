#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "game_manager.h"

namespace exam_project {

class PlayerWeaponHolder;

class Pistol : public ng::Node {
 public:
  Pistol(ng::App* app, const PlayerWeaponHolder* player_weapon_holder,
         const ng::Tilemap* tilemap, const GameManager* game_manager);
  void FlipY(bool is_flipped);

 protected:
  void Update() override;
  void Draw(sf::RenderTarget& target) override;

 private:
  const PlayerWeaponHolder* player_weapon_holder_ = nullptr;
  const ng::Tilemap* tilemap_ = nullptr;
  const GameManager* game_manager_ = nullptr;
  sf::Sprite arm_;
  sf::Sound shoot_sound_;
  ng::Node* shoot_point_ = nullptr;
};

}  // namespace exam_project