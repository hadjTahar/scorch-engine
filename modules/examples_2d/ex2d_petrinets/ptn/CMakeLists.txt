# imgui/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(ptn)

include_directories( "." )

file(GLOB_RECURSE CPP_Files *.h *.hpp *.cpp )
set(PROJECT_SOURCES
    ${CPP_Files}
)


# Add ImGui source files
add_library(ptn ${PROJECT_SOURCES})
