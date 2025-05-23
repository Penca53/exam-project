#include "game_manager.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>

#include "default_scene.h"
#include "engine/app.h"
#include "engine/node.h"
#include "lose_canvas.h"
#include "win_canvas.h"

namespace exam_project {

GameManager::GameManager(ng::App* app)
    : ng::Node(app),
      win_sound_(GetApp()->GetResourceManager().LoadSoundBuffer("Win_2.wav")),
      lose_sound_(
          GetApp()->GetResourceManager().LoadSoundBuffer("Loose_1.wav")) {}

void GameManager::OnAdd() {
  auto& lose_canvas = GetParent()->MakeChild<LoseCanvas>();
  lose_canvas_ = &lose_canvas;

  auto& win_canvas = GetParent()->MakeChild<WinCanvas>();
  win_canvas_ = &win_canvas;

  state_ = State::PLAY;
}

void GameManager::Update() {
  if (state_ == State::WON || state_ == State::LOST) {
    if (GetApp()->GetInput().GetKeyDown(sf::Keyboard::Scancode::Enter)) {
      GetApp()->LoadScene(MakeDefaultScene(GetApp()));
      return;
    }
  }
}

void GameManager::Boss() {
  if (state_ != State::PLAY) {
    return;
  }

  state_ = State::BOSS;
}

void GameManager::Win() {
  if (state_ != State::BOSS) {
    return;
  }

  state_ = State::WON;
  win_canvas_->Enable();
  win_sound_.play();
}

void GameManager::Lose() {
  if (state_ != State::PLAY && state_ != State::BOSS) {
    return;
  }

  state_ = State::LOST;
  lose_canvas_->Enable();
  lose_sound_.play();
}

GameManager::State GameManager::GetState() const {
  return state_;
}

void GameManager::CompleteSpawner() {
  ++completed_spawners_;
}

int32_t GameManager::GetCompletedSpawners() const {
  return completed_spawners_;
}

}  // namespace exam_project