#include "follow_player.h"

#include <SFML/System/Vector2.hpp>

#include "engine/app.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "player.h"

namespace exam_project {

FollowPlayer::FollowPlayer(ng::App* app, const Player* player)
    : ng::Node(app), player_(player) {}

void FollowPlayer::OnAdd() {
  Follow();
}

void FollowPlayer::Update() {
  Follow();
}

void FollowPlayer::Follow() {
  if (!GetScene()->IsValid(player_)) {
    return;
  }

  sf::Vector2f player_pos = player_->GetGlobalTransform().getPosition();
  GetParent()->SetLocalPosition(player_pos);
}

}  // namespace exam_project