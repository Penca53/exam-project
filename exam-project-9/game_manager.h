#pragma once

#include <SFML/Audio/Sound.hpp>
#include <cstdint>

#include "engine/node.h"
#include "lose_canvas.h"
#include "win_canvas.h"

namespace exam_project {

// Copied from jp-engine example game and adapted.
class GameManager : public ng::Node {
 public:
  enum class State : uint8_t {
    BEGIN = 0,
    PLAY,
    BOSS,
    WON,
    LOST,
  };

  explicit GameManager(ng::App* app);

  void Boss();
  void Win();
  void Lose();

  State GetState() const;

 protected:
  void OnAdd() override;
  void Update() override;

 private:
  State state_{};
  sf::Sound win_sound_;
  sf::Sound lose_sound_;

  LoseCanvas* lose_canvas_ = nullptr;
  WinCanvas* win_canvas_ = nullptr;
};

}  // namespace exam_project