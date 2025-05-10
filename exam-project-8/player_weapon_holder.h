#pragma once

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/node.h"
#include "engine/tilemap.h"

namespace exam_project {

class Pistol;
class Player;

class PlayerWeaponHolder : public ng::Node {
 public:
  PlayerWeaponHolder(ng::App* app, Player* player, const ng::Camera* camera,
                     const ng::Tilemap* tilemap);
  bool GetIsLargeBulletsEnabled() const;
  void SetIsLargeBulletsEnabled(bool enabled);

 protected:
  void Update() override;

 private:
  Player* player_ = nullptr;
  Pistol* pistol_ = nullptr;
  const ng::Camera* camera_ = nullptr;
  bool is_large_bullets_enabled = false;
};

}  // namespace exam_project