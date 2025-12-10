# Minions C++ Implementation

A high-performance C++ implementation of the Minions protocol with Python bindings.

## Status

🚧 **Work in Progress** 🚧

See [CPP_IMPLEMENTATION_PLAN.md](../CPP_IMPLEMENTATION_PLAN.md) for the full roadmap.

## Building

```bash
cd cpp
mkdir build && cd build
cmake .. -DBUILD_PYTHON_BINDINGS=ON
make -j$(nproc)
```

## Project Structure

```
cpp/
├── include/minions/       # Public headers
│   ├── core/              # Core types (Usage, Message)
│   ├── clients/           # LLM client interfaces
│   ├── protocols/         # Minion/Minions protocols
│   └── utils/             # Utilities (JSON, HTTP)
├── src/                   # Implementation files
├── bindings/              # Python bindings (pybind11)
├── tests/                 # Test suites
├── benchmarks/            # Performance benchmarks
└── examples/              # Usage examples
```

## Dependencies

- C++20 compiler (GCC 10+, Clang 12+, MSVC 2019+)
- CMake 3.16+
- nlohmann/json (fetched automatically)
- cpp-httplib (fetched automatically)
- pybind11 (for Python bindings)

## License

Same as the parent Minions project.

