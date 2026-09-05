cmake_minimum_required(VERSION 3.16)
project(qx_skia LANGUAGES CXX)


add_library(qx_skia STATIC IMPORTED)

### Find skia.lib and link it
### -------------------------
set(QX_SKIA_FILE_NAME "skia")

set( QX_CMK_SKIA_LIB_PATH "${CMAKE_SOURCE_DIR}/vendors/qx_skia/lib")
find_library(SKIA_LIB
    NAMES ${QX_SKIA_FILE_NAME}
    PATHS ${QX_CMK_SKIA_LIB_PATH})

message( "**************************" )
message( ${QX_SKIA_FILE_NAME} )
message( ${SKIA_LIB} )
if(SKIA_LIB)
    message(STATUS "Skia library found at: ${SKIA_LIB}")
else()
    message(FATAL_ERROR "QX-Error: No ${QX_SKIA_LIB_FILE} in: ${QX_CMK_SKIA_LIB_PATH}")
endif()
target_link_libraries(qx_core PRIVATE ${SKIA_LIB})
