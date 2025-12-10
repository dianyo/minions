/**
 * @file base.hpp
 * @brief Abstract base class for all LLM clients
 * 
 * This mirrors the Python minions/clients/base.py implementation.
 * All concrete clients (Ollama, OpenAI, etc.) inherit from this.
 */

#ifndef MINIONS_CLIENTS_BASE_HPP
#define MINIONS_CLIENTS_BASE_HPP

#include <minions/core/usage.hpp>
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <tuple>
#include <optional>
#include <memory>
#include <functional>

namespace minions {

/**
 * @brief Message structure for chat completions
 */
struct Message {
    std::string role;     // "system", "user", "assistant"
    std::string content;
    
    // Optional: for multimodal
    std::optional<std::vector<std::string>> images;
    
    // JSON conversion
    [[nodiscard]] nlohmann::json to_json() const {
        nlohmann::json j = {
            {"role", role},
            {"content", content}
        };
        if (images && !images->empty()) {
            j["images"] = *images;
        }
        return j;
    }
    
    static Message from_json(const nlohmann::json& j) {
        Message m;
        m.role = j.at("role").get<std::string>();
        m.content = j.at("content").get<std::string>();
        if (j.contains("images")) {
            m.images = j.at("images").get<std::vector<std::string>>();
        }
        return m;
    }
};

/**
 * @brief Result of a chat completion
 */
struct ChatResult {
    std::vector<std::string> responses;
    Usage usage;
    std::vector<std::string> finish_reasons;
};

/**
 * @brief Abstract base class for LLM clients
 * 
 * All clients must implement the chat() method.
 * This provides a consistent interface across different providers.
 */
class Client {
public:
    virtual ~Client() = default;
    
    /**
     * @brief Perform a chat completion
     * 
     * @param messages List of messages in the conversation
     * @param kwargs Additional provider-specific parameters
     * @return ChatResult containing responses, usage, and finish reasons
     */
    virtual ChatResult chat(
        const std::vector<Message>& messages,
        const nlohmann::json& kwargs = {}
    ) = 0;
    
    /**
     * @brief Get the model name
     */
    [[nodiscard]] virtual std::string model_name() const = 0;
    
    /**
     * @brief Check if client supports embeddings
     */
    [[nodiscard]] virtual bool supports_embeddings() const { return false; }
    
    /**
     * @brief Generate embeddings (optional)
     */
    virtual std::vector<std::vector<float>> embed(
        const std::vector<std::string>& texts
    ) {
        throw std::runtime_error("Embeddings not supported by this client");
    }
    
protected:
    // Common configuration
    float temperature_ = 0.7f;
    int max_tokens_ = 2048;
    bool verbose_ = false;
};

/**
 * @brief Type alias for client pointer
 */
using ClientPtr = std::shared_ptr<Client>;

} // namespace minions

#endif // MINIONS_CLIENTS_BASE_HPP

