cmake_minimum_required(VERSION 3.16)


add_subdirectory( qx            qx_build )
add_subdirectory( examples_2d   examples_2d_build)
add_subdirectory( examples_3d   examples_3d_build)
# add_subdirectory( tests         tests_build)
# add_subdirectory( benchmarks    benchmarks_build)


### Add "apps", only if it exists
if(EXISTS "apps/CMakeLists.txt")
    add_subdirectory( apps          apps_build)
endif()