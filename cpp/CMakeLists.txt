cmake_minimum_required(VERSION 3.16)
project(minions_cpp 
    VERSION 0.1.0 
    LANGUAGES CXX
    DESCRIPTION "C++ implementation of the Minions protocol"
)

# ============================================================================
# Options
# ============================================================================
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# ============================================================================
# C++ Standard
# ============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Dependencies (FetchContent)
# ============================================================================
include(FetchContent)

# nlohmann/json - Header-only JSON library
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

# cpp-httplib - Header-only HTTP library
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.15.3
)

# spdlog - Fast logging library
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(json httplib spdlog)

# ============================================================================
# Main Library
# ============================================================================
add_library(minions_cpp STATIC
    # Core
    # src/core/usage.cpp
    # src/core/types.cpp
    
    # Clients
    # src/clients/base.cpp
    # src/clients/ollama.cpp
    # src/clients/openai.cpp
    
    # Protocols
    # src/protocols/minion.cpp
    # src/protocols/minions.cpp
    
    # Utils
    # src/utils/json.cpp
    # src/utils/http.cpp
    # src/utils/chunking.cpp
)

# For now, create a placeholder source file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/placeholder.cpp "// Placeholder\n")
target_sources(minions_cpp PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/placeholder.cpp)

target_include_directories(minions_cpp 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(minions_cpp
    PUBLIC
        nlohmann_json::nlohmann_json
        httplib::httplib
        spdlog::spdlog
)

# Compiler warnings
target_compile_options(minions_cpp PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# ============================================================================
# Python Bindings
# ============================================================================
if(BUILD_PYTHON_BINDINGS)
    find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
    
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.12.0
    )
    FetchContent_MakeAvailable(pybind11)
    
    pybind11_add_module(minions_cpp_py 
        bindings/minions_cpp.cpp
    )
    
    target_link_libraries(minions_cpp_py PRIVATE minions_cpp)
    
    # Output to a convenient location
    set_target_properties(minions_cpp_py PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bindings
    )
endif()

# ============================================================================
# Tests
# ============================================================================
if(BUILD_TESTS)
    enable_testing()
    
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)
    
    # Add test executables here as you implement
    # add_executable(test_usage tests/unit/test_usage.cpp)
    # target_link_libraries(test_usage PRIVATE minions_cpp Catch2::Catch2WithMain)
    # add_test(NAME test_usage COMMAND test_usage)
endif()

# ============================================================================
# Benchmarks
# ============================================================================
if(BUILD_BENCHMARKS)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.3
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(benchmark)
    
    # Add benchmark executables here as you implement
    # add_executable(bench_protocol benchmarks/bench_protocol.cpp)
    # target_link_libraries(bench_protocol PRIVATE minions_cpp benchmark::benchmark)
endif()

# ============================================================================
# Examples
# ============================================================================
if(BUILD_EXAMPLES)
    # Add example executables here as you implement
    # add_executable(simple_minion examples/simple_minion.cpp)
    # target_link_libraries(simple_minion PRIVATE minions_cpp)
endif()

# ============================================================================
# Installation
# ============================================================================
include(GNUInstallDirs)

install(TARGETS minions_cpp
    EXPORT minions_cpp-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/minions
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ============================================================================
# Summary
# ============================================================================
message(STATUS "")
message(STATUS "=== Minions C++ Configuration ===")
message(STATUS "Version:           ${PROJECT_VERSION}")
message(STATUS "C++ Standard:      ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "Python Bindings:   ${BUILD_PYTHON_BINDINGS}")
message(STATUS "Tests:             ${BUILD_TESTS}")
message(STATUS "Benchmarks:        ${BUILD_BENCHMARKS}")
message(STATUS "Examples:          ${BUILD_EXAMPLES}")
message(STATUS "")

