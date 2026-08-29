cmake_minimum_required(VERSION 3.16)

### ----------------
### App Options
### ----------------


set( QX_CMK_APP_NAME ex2d_openmp_check )
set( QX_CMK_ORG_NAME "QxOrg" )

# find_package(OpenMP REQUIRED)

include( "${CMAKE_SOURCE_DIR}/cmakes/app.cmake" )
# target_link_libraries( openmp_check PUBLIC OpenMP::OpenMP_CXX)
qx_use_module( canvas_skia_raster_surface )
