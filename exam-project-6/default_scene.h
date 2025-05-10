#pragma once

#include <memory>

#include "engine/app.h"
#include "engine/scene.h"

namespace exam_project {

std::unique_ptr<ng::Scene> MakeDefaultScene(ng::App* app);

}  // namespace exam_project