#include <SFML/System/Vector2.hpp>
#include <cstdlib>

#include "default_scene.h"
#include "engine/app.h"

int main() {
  static constexpr sf::Vector2u kWindowSize = {832U, 640U};
  ng::App app(kWindowSize, "Exam Project", 60, 60);
  app.LoadScene(exam_project::MakeDefaultScene(&app)).Run();
  return EXIT_SUCCESS;
}
