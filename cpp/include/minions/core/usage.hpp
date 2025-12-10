/**
 * @file usage.hpp
 * @brief Token usage tracking for LLM API calls
 *
 * This mirrors the Python minions/usage.py implementation.
 */

#ifndef MINIONS_CORE_USAGE_HPP
#define MINIONS_CORE_USAGE_HPP

#include <nlohmann/json.hpp>
#include <cstdint>

namespace minions
{

    /**
     * @brief Tracks token usage across LLM API calls
     *
     * Thread-safe accumulator for prompt and completion tokens.
     * Supports addition for aggregating usage across multiple calls.
     *
     * @example
     * ```cpp
     * Usage total;
     * auto [response, usage] = client.chat(messages);
     * total += usage;
     * std::cout << "Total tokens: " << total.total_tokens() << std::endl;
     * ```
     */
    class Usage
    {
    public:
        int64_t prompt_tokens = 0;
        int64_t completion_tokens = 0;

        /**
         * @brief Default constructor - zero usage
         */
        Usage() = default;

        /**
         * @brief Construct with initial values
         */
        Usage(int64_t prompt, int64_t completion)
            : prompt_tokens(prompt), completion_tokens(completion) {}

        /**
         * @brief Get total token count
         */
        [[nodiscard]] int64_t total_tokens() const
        {
            return prompt_tokens + completion_tokens;
        }

        /**
         * @brief Accumulate usage from another Usage object
         */
        Usage &operator+=(const Usage &other)
        {
            prompt_tokens += other.prompt_tokens;
            completion_tokens += other.completion_tokens;
            return *this;
        }

        /**
         * @brief Add two Usage objects
         */
        [[nodiscard]] Usage operator+(const Usage &other) const
        {
            return Usage(
                prompt_tokens + other.prompt_tokens,
                completion_tokens + other.completion_tokens);
        }

        /**
         * @brief Convert to JSON object
         */
        [[nodiscard]] nlohmann::json to_dict() const
        {
            return {
                {"prompt_tokens", prompt_tokens},
                {"completion_tokens", completion_tokens},
                {"total_tokens", total_tokens()}};
        }

        /**
         * @brief Create from JSON object
         */
        static Usage from_dict(const nlohmann::json &j)
        {
            return Usage(
                j.value("prompt_tokens", 0),
                j.value("completion_tokens", 0));
        }
    };

    /**
     * @brief JSON serialization support
     */
    inline void to_json(nlohmann::json &j, const Usage &u)
    {
        j = u.to_dict();
    }

    inline void from_json(const nlohmann::json &j, Usage &u)
    {
        u = Usage::from_dict(j);
    }

} // namespace minions

#endif // MINIONS_CORE_USAGE_HPP
