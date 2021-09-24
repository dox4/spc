#include <cassert>
#include <functional>
#include <optional>
#include <string_view>

template <typename T> class ParserResult {
    std::optional<T> _match;
    // const string_view _err_msg;
    const std::string_view _rest;

  public:
    explicit ParserResult(const T value, const std::string_view rest)
        : _match(value), _rest(rest) {}
    explicit ParserResult(const std::string_view rest)
        : _match(std::nullopt), _rest(rest) {}
    bool succeed() const noexcept { return _match.has_value(); }
    const T value() const {
        if (_match.has_value())
            return _match.value();
        assert(0);
    }
    const std::string_view& rest() const noexcept {
        return _rest;
    }
};

template <typename T>
using Parser = std::function<const ParserResult<T>(const std::string_view &)>;
