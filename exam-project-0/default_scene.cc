#include "default_scene.h"

#include <memory>

#include "engine/app.h"
#include "engine/camera.h"
#include "engine/layer.h"
#include "engine/scene.h"
#include "player.h"

namespace exam_project {

std::unique_ptr<ng::Scene> MakeDefaultScene(ng::App* app) {
  auto scene = std::make_unique<ng::Scene>(app);
  scene->SetName("Scene");

  scene->MakeChild<Player>();

  scene->MakeChild<ng::Camera>(1, ng::Layer::kUI);
  scene->MakeChild<ng::Camera>();

  return scene;
}

}  // namespace exam_project