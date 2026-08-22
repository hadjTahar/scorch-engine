cmake_minimum_required(VERSION 3.16)
project(examples_3d LANGUAGES CXX)



add_subdirectory( ecs ) ## OK
# add_subdirectory( ecs_boids ) ## X
add_subdirectory( ecs_collisions ) ## OK


add_subdirectory( ecs_rendering_static_count ) ## OK
add_subdirectory( ecs_rendering_dynamic_count ) ## OK

add_subdirectory( collision_tree ) ## OK
add_subdirectory( camera_controls ) ## OK
add_subdirectory( circle ) ## OK
add_subdirectory( circles ) ## OK
add_subdirectory( rotating_cube ) ## OK
add_subdirectory( rotating_cubes ) ## OK
