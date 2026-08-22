cmake_minimum_required(VERSION 3.16)
project(examples_2d LANGUAGES CXX)



add_subdirectory( sample )

add_subdirectory( property )
# add_subdirectory( fails ) X
add_subdirectory( timer )
add_subdirectory( paths )
add_subdirectory( assets )
add_subdirectory( motions )
add_subdirectory( position )
add_subdirectory( velocity )
add_subdirectory( reactive )
add_subdirectory( camera )
add_subdirectory( gradients )
add_subdirectory( rounded )
add_subdirectory( canvas_paths )

add_subdirectory( texts )
add_subdirectory( images )
add_subdirectory( flexLayout )
add_subdirectory( mouse )
add_subdirectory( keys )
add_subdirectory( inputs )
add_subdirectory( sml )
add_subdirectory( openmp_check )
add_subdirectory( z_sorting )


