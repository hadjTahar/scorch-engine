project( ${QX_CMK_APP_NAME}
    VERSION 1.0
    LANGUAGES CXX
)



# Src files
file(GLOB_RECURSE SRC_FILES *.h *.cpp *.md)

# Add src files
add_executable(${QX_CMK_APP_NAME} ${SRC_FILES} )
# C++20
target_compile_features(${QX_CMK_APP_NAME} PUBLIC cxx_std_20)
# Header includes
# target_include_directories(${QX_CMK_APP_NAME} PUBLIC  "${CMAKE_SOURCE_DIR}/qx")
# Link qx
target_link_libraries( ${QX_CMK_APP_NAME} PUBLIC qx )



# Header includes
# target_include_directories( ${QX_CMK_APP_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/benchmarks/benchmark/include" )
# target_include_directories( ${QX_CMK_APP_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/vendors/benchmarks/benchmark/include" )


# # Link to googletest
target_link_libraries( ${QX_CMK_APP_NAME} PUBLIC benchmark::benchmark )

