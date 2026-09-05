# Compile time defs
### ---------------

if(MSVC)
    target_compile_definitions( qx_core PUBLIC "QX_DEF_UNIQUE_ADDRESS=[[msvc::no_unique_address]]" )
else()
    target_compile_definitions( qx_core PUBLIC "QX_DEF_UNIQUE_ADDRESS=[[no_unique_address]]" )
endif()


target_compile_definitions( qx_core PUBLIC QX_DEF_SDL_WINDOW_OPTIONS=${QX_OPT_SDL_WINDOW_OPTIONS} )
target_compile_definitions( qx_core PUBLIC QX_DEF_SDL_INIT_OPTIONS=${QX_OPT_SDL_INIT_OPTIONS} )

target_compile_definitions( qx_core PUBLIC "QX_DEF_DEBUG_DETAILS=${QX_OPT_DEBUG_DETAILS}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_DEBUG_LEVEL=${QX_OPT_DEBUG_LEVEL}" )




target_compile_definitions( qx_core PUBLIC "QX_DEF_ENABLE_META_DEBUGGING=${QX_OPT_ENABLE_META_DEBUGGING}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_ENABLE_PRINT_SIZES=${QX_OPT_ENABLE_PRINT_SIZES}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_ENABLE_FPS_PROBE=${QX_OPT_ENABLE_FPS_PROBE}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_USE_COMPILED_ASSETS=${QX_OPT_USE_COMPILED_ASSETS}" )
if( QX_OPT_USE_COMPILED_ASSETS )
    target_compile_definitions( qx_core PUBLIC "QX_DEF_INC_COMPILED_ASSETS" )
endif()

target_compile_definitions( qx_core PUBLIC "QX_DEF_TYPED_FUNCTION_CALLBACK=${QX_OPT_TYPED_FUNCTION_CALLBACK}" )

target_compile_definitions( qx_core PUBLIC "QX_DEF_IMMEDIATE_EVENTS=${QX_OPT_IMMEDIATE_EVENTS}" )


target_compile_definitions( qx_core PUBLIC "QX_DEF_ENABLE_2D_Z_SORTING=${QX_OPT_ENABLE_2D_Z_SORTING}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_MAX_HIERARCHY_LEVEL=${QX_OPT_MAX_HIERARCHY_LEVEL}" )



### --------------------------------------------------------------------------------



if("${QX_OPT_PROCESS_COMPONENTS_SORT}" STREQUAL "SEQ")
    target_compile_definitions( qx_core PUBLIC "QX_DEF_PROCESS_COMPONENTS_SORT=std::execution::seq" )
elseif("${QX_OPT_PROCESS_COMPONENTS_SORT}" STREQUAL "UNSEQ")
    target_compile_definitions( qx_core PUBLIC "QX_DEF_PROCESS_COMPONENTS_SORT=std::execution::unseq" )
elseif("${QX_OPT_PROCESS_COMPONENTS_SORT}" STREQUAL "PAR")
    target_compile_definitions( qx_core PUBLIC "QX_DEF_PROCESS_COMPONENTS_SORT=std::execution::par" )
elseif("${QX_OPT_PROCESS_COMPONENTS_SORT}" STREQUAL "PAR_UNSEQ")
    target_compile_definitions( qx_core PUBLIC "QX_DEF_PROCESS_COMPONENTS_SORT=std::execution::par_unseq" )
else()
    message(FATAL_ERROR "QX-Error: Unsupported QX_OPT_PROCESS_COMPONENTS_SORT type ")
endif()


### --------------------------------------------------------------------------------

target_compile_definitions( qx_core PUBLIC "QX_DEF_TYPED_FUNCTION_CAPTURE_SIZE=${QX_OPT_TYPED_FUNCTION_CAPTURE_SIZE}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_DROP_FRAME_DELAY=${QX_OPT_DROP_FRAME_DELAY}" )

target_compile_definitions( qx_core PUBLIC "QX_DEF_VERTEX_COUNT_WARNNING=${QX_OPT_VERTEX_COUNT_WARNNING}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_INDEX_COUNT_WARNNING=${QX_OPT_INDEX_COUNT_WARNNING}" )
target_compile_definitions( qx_core PUBLIC "QX_DEF_3D_GEOMETRY_TRACKERS=${QX_OPT_3D_GEOMETRY_TRACKERS}" )






### --------------------------------------------------------------------------------

