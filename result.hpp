#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>
#include <variant>

template <typename T, typename E>
class Result {
private:
    // issue here is T != E has to be true
    std::variant<T, E> result;

public:
    static_assert(!std::is_same_v<T, E>, "T and E must be different types");

    constexpr Result(const T& success)
        : result(success)
    {
    }
    constexpr Result(const E& error)
        : result(error)
    {
    }

    static constexpr Result Ok(const T& success) noexcept { return Result(success); }
    static constexpr Result Err(const E& error) noexcept { return Result(error); }

    [[nodiscard]] constexpr bool is_ok() const noexcept { return std::holds_alternative<T>(this->result); }
    [[nodiscard]] constexpr bool is_err() const noexcept { return std::holds_alternative<E>(this->result); }

    [[nodiscard]] T unwrap() const
    {
        if (this->is_ok()) {
            return std::get<T>(this->result);
        } else {
            throw std::runtime_error("Attempted to unwrap an Err");
        }
    }

    [[nodiscard]] T expect(std::string message) const
    {
        if (this->is_ok()) {
            return std::get<T>(this->result);
        } else {
            throw std::runtime_error(message);
        }
    }

    template <typename Fn, typename U = std::invoke_result_t<Fn, T>>
    Result<U, E> and_then(Fn&& func) noexcept
    {
        if constexpr (std::is_invocable_v<Fn, T>) {
            if (this->is_ok()) {
                return std::invoke(std::forward<Fn>(func), std::get<T>(this->result));
            } else {
                return *this;
            }
        } else {
            return *this;
        }
    }

    template <typename Fn, typename U = std::invoke_result_t<Fn, E>>
    Result<T, U> or_else(Fn&& func) noexcept
    {
        if constexpr (std::is_invocable_v<Fn, T>) {
            if (this->is_err()) {
                return std::invoke(std::forward<Fn>(func), std::get<T>(this->result));
            } else {
                return *this;
            }
        } else {
            return *this;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Result& result)
    {
        if (result.is_ok()) {
            os << "Ok(" << std::get<T>(result.result) << ")\n";
        } else {
            os << "Err(" << std::get<E>(result.result) << ")\n";
        }
        return os;
    }
};
