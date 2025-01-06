// Copyright 2022 Olaf <ibis-hdl@users.noreply.github.com>.
// SPDX-License-Identifier: GPL-3.0-only

#include <string_view>
#include <string>
#include <format>
#include <iostream>
#include <cstdint>

//
// clang-18 has problems with format's call to consteval function, see
// https://godbolt.org/z/W814sKExr
//

struct foo_literal {
    enum class specifier_type : std::uint8_t { unspecified, A, B, C };

    std::string_view literal;
    specifier_type specifier;
};

template <>
struct std::formatter<foo_literal::specifier_type> : std::formatter<std::string_view> {
    auto format(foo_literal::specifier_type specifier, std::format_context& ctx) const
    {
        using specifier_type = foo_literal::specifier_type;
        using namespace std::literals::string_view_literals;

        switch (specifier) {
            case specifier_type::A:
                return std::formatter<std::string_view>::format("a"sv, ctx);
            case specifier_type::B:
                return std::formatter<std::string_view>::format("b"sv, ctx);
            case specifier_type::C:
                return std::formatter<std::string_view>::format("c"sv, ctx);
            default:
                return std::formatter<std::string_view>::format("?"sv, ctx);
        }
        return ctx.out();
    }
};

template <>
struct std::formatter<foo_literal> : std::formatter<std::string_view> {
    auto format(foo_literal const& bit_string, std::format_context& ctx) const
    {
        std::string literal;

        std::format_to(std::back_inserter(literal), "{}:{}", bit_string.specifier,
                       bit_string.literal);

        return std::formatter<std::string_view>::format(literal, ctx);
    }
};

void print(std::ostream& os, std::string_view name) { os << std::format("Hello {0}!\n", name); }

std::string library_info()
{
#if (_LIBCPP_VERSION)
    return std::format("LibC++ {:d}", _LIBCPP_VERSION);
#elif (__GLIBCXX__)
    return std::format("GlibC++ {:d}", __GLIBCXX__);
#elif (_MSC_VER)
    return std::format("MSVC C++ {}", _MSC_VER);
#else
    constexpr std::string_view const na{ "Unknown" };
    return std::format("{}", na);
#endif
}

int main()
{
    print(std::cout, "World");

    foo_literal literal{ "Hello", foo_literal::specifier_type::A };
    std::cout << std::format("{: ^10}\n", literal);

    print(std::cout, std::format("... from {}\n", library_info()));

    return 0;
}
