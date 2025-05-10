add_executable(exam-project-5 main.cc default_scene.cc enemy_spawner.cc follow_player.cc ghost.cc pistol_bullet.cc pistol.cc player.cc player_weapon_holder.cc)

target_compile_features(exam-project-5 PRIVATE cxx_std_23)
set_target_properties(exam-project-5 PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(exam-project-5 PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

if (NOT MSVC) 
  target_compile_options(exam-project-5 PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address,undefined>)
  target_link_options(exam-project-5 PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address,undefined>)
endif()

target_link_libraries(exam-project-5 PRIVATE jp-engine)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if (CLANG_TIDY_EXE)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")

    set_target_properties(exam-project-5 PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
else()
    message("Clang Tidy not found")
endif()

add_custom_target(copy_resources-5
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:exam-project-5>/resources"
)
add_dependencies(exam-project-5 copy_resources-5)