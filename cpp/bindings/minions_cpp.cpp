/**
 * @file minions_cpp.cpp
 * @brief Python bindings for the Minions C++ library
 * 
 * This file uses pybind11 to expose the C++ implementation to Python,
 * enabling gradual migration and performance comparison.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// TODO: Include headers as they are implemented
// #include <minions/core/usage.hpp>
// #include <minions/clients/ollama.hpp>
// #include <minions/protocols/minion.hpp>

namespace py = pybind11;

PYBIND11_MODULE(minions_cpp_py, m) {
    m.doc() = "Minions C++ - High-performance implementation of the Minions protocol";
    
    // ========================================================================
    // Core Types
    // ========================================================================
    
    // TODO: Uncomment and implement as you build each module
    
    /*
    py::class_<minions::Usage>(m, "Usage")
        .def(py::init<>())
        .def_readwrite("prompt_tokens", &minions::Usage::prompt_tokens)
        .def_readwrite("completion_tokens", &minions::Usage::completion_tokens)
        .def_property_readonly("total_tokens", &minions::Usage::total_tokens)
        .def("__iadd__", &minions::Usage::operator+=)
        .def("to_dict", &minions::Usage::to_dict);
    */
    
    // ========================================================================
    // Clients
    // ========================================================================
    
    /*
    py::class_<minions::OllamaClient>(m, "OllamaClient")
        .def(py::init<const std::string&, float, int>(),
             py::arg("model_name"),
             py::arg("temperature") = 0.7,
             py::arg("max_tokens") = 2048)
        .def("chat", &minions::OllamaClient::chat,
             py::arg("messages"),
             py::arg("kwargs") = py::dict());
    
    py::class_<minions::OpenAIClient>(m, "OpenAIClient")
        .def(py::init<const std::string&, const std::string&>(),
             py::arg("model_name"),
             py::arg("api_key") = "")
        .def("chat", &minions::OpenAIClient::chat);
    */
    
    // ========================================================================
    // Protocols
    // ========================================================================
    
    /*
    py::class_<minions::Minion>(m, "Minion")
        .def(py::init<
             std::shared_ptr<minions::Client>,
             std::shared_ptr<minions::Client>,
             int,
             std::function<void(const std::string&, const py::dict&, bool)>
        >(),
             py::arg("local_client"),
             py::arg("remote_client"),
             py::arg("max_rounds") = 3,
             py::arg("callback") = nullptr)
        .def("__call__", &minions::Minion::operator(),
             py::arg("task"),
             py::arg("context"),
             py::arg("max_rounds") = py::none());
    */
    
    // ========================================================================
    // Version Info
    // ========================================================================
    
    m.attr("__version__") = "0.1.0";
    m.attr("__cpp__") = true;  // Flag to identify C++ backend
}

