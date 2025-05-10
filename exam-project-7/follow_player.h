#pragma once

#include "engine/app.h"
#include "engine/node.h"
#include "player.h"

namespace exam_project {

class FollowPlayer : public ng::Node {
 public:
  FollowPlayer(ng::App* app, const Player* player);

 protected:
  void OnAdd() override;
  void Update() override;

 private:
  void Follow();

  const Player* player_ = nullptr;
};

}  // namespace exam_project