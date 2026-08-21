# 1. Find the Python interpreter
find_package(Python3 REQUIRED)

# 2. Execute the command during configuration
execute_process(
    COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_SOURCE_DIR}/scripts/assets_compiler/compileAssets.py"
            ${CMAKE_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${QX_OPT_USE_COMPILED_ASSETS}

    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE PYTHON_RESULT
    OUTPUT_VARIABLE PYTHON_OUTPUT
    ERROR_VARIABLE PYTHON_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 3. Handle the output
if(PYTHON_RESULT EQUAL 0)
    message(STATUS "Python output: ${PYTHON_OUTPUT}")
else()
    message(FATAL_ERROR "QX-Error: Python command failed: ${PYTHON_ERROR}")
endif()
