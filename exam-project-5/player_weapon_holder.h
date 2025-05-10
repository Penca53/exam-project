#pragma once

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/node.h"
#include "engine/tilemap.h"
#include "pistol.h"
#include "player.h"

namespace exam_project {

class PlayerWeaponHolder : public ng::Node {
 public:
  PlayerWeaponHolder(ng::App* app, Player* player, const ng::Camera* camera,
                     const ng::Tilemap* tilemap);

 protected:
  void Update() override;

 private:
  Player* player_ = nullptr;
  Pistol* pistol_ = nullptr;
  const ng::Camera* camera_ = nullptr;
};

}  // namespace exam_project