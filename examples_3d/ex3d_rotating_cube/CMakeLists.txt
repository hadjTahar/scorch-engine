cmake_minimum_required(VERSION 3.16)

### ----------------
### App Options
### ----------------


set( QX_CMK_APP_NAME ex3d_rotating_cube )
set( QX_CMK_ORG_NAME "QxOrg" )

include( "${CMAKE_SOURCE_DIR}/cmakes/app.cmake" )


qx_use_module( render_backend_sample )
qx_use_module( render_backend_filament )