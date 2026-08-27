project( ${QX_CMK_APP_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

include( "${CMAKE_SOURCE_DIR}/cmakes/assets.cmake" )

### ----------------
### Set variables
### ----------------

if( QX_OPT_SDL_STATIC_BUILD )
    set( BUILD_STATIC_LIBS   ON  )
    set( BUILD_SHARED_LIBS   OFF )
    set( QX_CMK_SDL_LIB_NAME    "SDL3-static")
else()
    set( BUILD_STATIC_LIBS   OFF )
    set( BUILD_SHARED_LIBS   ON  )
    set( QX_CMK_SDL_LIB_NAME    "SDL3")
endif()


### Compiler specifics
if (WIN32 AND MSVC AND QX_OPT_SDL_STATIC_BUILD)
    set( QX_CMK_SYSTEM_LIBS
        # Windows system libs required by SDL static
        winmm
        setupapi
        cfgmgr32
        imm32
        version
        user32
        gdi32
        ole32
        shell32
        advapi32
    )
endif()

# Src files
file(GLOB_RECURSE SRC_FILES *.h *.cpp *.md)

# Add src files
add_executable(${QX_CMK_APP_NAME} ${SRC_FILES} )
# C++20
target_compile_features(${QX_CMK_APP_NAME} PUBLIC cxx_std_20)


function( qx_app_use_module module )
    cmake_language(CALL qx_link_${module} ${QX_CMK_APP_NAME})
endfunction()

qx_app_use_module( qx )

target_compile_definitions( ${QX_CMK_APP_NAME} PUBLIC "QX_DEF_APP_NAME=\"${QX_CMK_APP_NAME}\"" )
target_compile_definitions( ${QX_CMK_APP_NAME} PUBLIC "QX_DEF_ORG_NAME=\"${QX_CMK_ORG_NAME}\"" )
target_compile_definitions( ${QX_CMK_APP_NAME} PUBLIC "QX_DEF_APP_SRC=\"${CMAKE_CURRENT_SOURCE_DIR}\"" )

if (WIN32 AND MSVC AND QX_OPT_SDL_STATIC_BUILD)
    ### Hide console
    set_target_properties(${QX_CMK_APP_NAME} PROPERTIES
           WIN32_EXECUTABLE TRUE
       )
endif()

