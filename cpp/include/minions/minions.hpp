/**
 * @file minions.hpp
 * @brief Main include file for the Minions C++ library
 * 
 * Include this single header to access all Minions functionality.
 * 
 * @example
 * ```cpp
 * #include <minions/minions.hpp>
 * 
 * int main() {
 *     auto local = minions::OllamaClient("llama3.2");
 *     auto remote = minions::OpenAIClient("gpt-4o");
 *     
 *     auto minion = minions::Minion(local, remote);
 *     auto result = minion("What is the diagnosis?", {"Patient record..."});
 *     
 *     std::cout << result.final_answer << std::endl;
 *     return 0;
 * }
 * ```
 */

#ifndef MINIONS_MINIONS_HPP
#define MINIONS_MINIONS_HPP

// Core types
// #include <minions/core/types.hpp>
// #include <minions/core/usage.hpp>

// Clients
// #include <minions/clients/base.hpp>
// #include <minions/clients/ollama.hpp>
// #include <minions/clients/openai.hpp>

// Protocols
// #include <minions/protocols/minion.hpp>
// #include <minions/protocols/minions.hpp>

// Utils
// #include <minions/utils/json.hpp>
// #include <minions/utils/chunking.hpp>

namespace minions {

/// Library version
constexpr const char* VERSION = "0.1.0";

} // namespace minions

#endif // MINIONS_MINIONS_HPP

