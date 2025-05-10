#pragma once

#include "engine/app.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class GoblinPistol;
class Goblin;
class Player;

class GoblinWeaponHolder : public ng::Node {
 public:
  GoblinWeaponHolder(ng::App* app, Goblin* goblin, Player* player,
                     const ng::Tilemap* tilemap);

 protected:
  void Update() override;

 private:
  Goblin* goblin_ = nullptr;
  Player* player_ = nullptr;
  GoblinPistol* goblin_pistol_ = nullptr;
};

}  // namespace exam_project