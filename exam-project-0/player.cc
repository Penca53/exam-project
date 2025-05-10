#include "player.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "engine/app.h"
#include "engine/input.h"
#include "engine/node.h"
#include "engine/resource_manager.h"
#include "player_weapon_holder.h"

namespace exam_project {

Player::Player(ng::App* app)
    : ng::Node(app),
      head_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Player/head.png")),
      body_(GetApp()->GetResourceManager().LoadTexture(
          "Sprites/Player/body.png")) {
  head_.setOrigin({4, 2});
  head_.setPosition({0, -4 * 4});
  body_.setOrigin({4, 2});

  head_.setScale({4, 4});
  body_.setScale({4, 4});

  MakeChild<PlayerWeaponHolder>(this);
}

void Player::FlipX(bool is_flipped) {
  head_.setScale({is_flipped ? -4.F : 4.F, 4});
}

void Player::Update() {
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

  if (direction.lengthSquared() > 0) {
    static constexpr float kMovementSpeed = 4.F;
    Translate(direction.normalized() * kMovementSpeed);
  }
}

void Player::Draw(sf::RenderTarget& target) {
  target.draw(head_, GetGlobalTransform().getTransform());
  target.draw(body_, GetGlobalTransform().getTransform());
}

}  // namespace exam_project
