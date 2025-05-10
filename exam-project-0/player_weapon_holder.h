#pragma once

#include "engine/app.h"
#include "engine/node.h"
#include "pistol.h"
#include "player.h"

namespace exam_project {

class PlayerWeaponHolder : public ng::Node {
 public:
  explicit PlayerWeaponHolder(ng::App* app, Player* player);

 protected:
  void Update() override;

 private:
  Player* player_ = nullptr;
  Pistol* pistol_ = nullptr;
};

}  // namespace exam_project