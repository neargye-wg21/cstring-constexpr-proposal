// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstring.hpp>
#include <cwchar.hpp>
namespace proposal = nstd;

#include <array>
#include <cstring>
#include <iterator>

constexpr bool is_same_signedness(int lhs, int rhs) noexcept {
  if (lhs < 0) {
    return rhs < 0;
  } else if (lhs > 0) {
    return rhs > 0;
  } else if (lhs == 0) {
    return rhs == 0;
  }

  return lhs == rhs;
}

TEST_CASE("wcscpy") {
  constexpr std::array<wchar_t, 7> char_array = {L'1', L'2', L'3', L'4', L'5', L'6', L'\0'};
  auto test_strcpy = [](const wchar_t* str) constexpr {
    std::array<wchar_t, 32> m = {};
    proposal::wcscpy(m.data(), str);
    return m;
  };

  constexpr auto char_array_cpy = test_strcpy(char_array.data());
  static_assert(proposal::wcscmp(char_array_cpy.data(), char_array.data()) == 0);
  REQUIRE(std::wcscmp(char_array_cpy.data(), char_array.data()) == 0);
}

TEST_CASE("wcsncpy") {
  constexpr std::array<wchar_t, 7> char_array = {L'1', L'2', L'3', L'4', L'5', L'6', L'\0'};
  constexpr auto n = 5;
  auto test_strncpy = [](const wchar_t* str, std::size_t n) constexpr {
    std::array<wchar_t, 32> m = {};
    proposal::wcsncpy(m.data(), str, n);
    return m;
  };

  constexpr auto char_array_cpy = test_strncpy(char_array.data(), n);
  static_assert(proposal::wcsncmp(char_array_cpy.data(), char_array.data(), n) == 0);
  REQUIRE(std::wcsncmp(char_array_cpy.data(), char_array.data(), n) == 0);
}

TEST_CASE("wcscat") {
  auto test_strcat = []() constexpr {
    wchar_t str1[50] = L"Hello ";
    wchar_t str2[50] = L"World!";
    proposal::wcscat(str1, str2);
    return proposal::wcscmp(str1, L"Hello World!") == 0;
  };

  constexpr bool b = test_strcat();
  static_assert(b);
}

TEST_CASE("wcsncat") {
  auto test_strncat = []() constexpr {
    const std::size_t n = 3;
    wchar_t str1[50] = L"Hello ";
    wchar_t str2[50] = L"World!";
    proposal::wcsncat(str1, str2, n);
    return proposal::wcsncmp(str1, L"Hello World!", proposal::wcslen(str1)) == 0;
  };

  constexpr bool b = test_strncat();
  static_assert(b);
}

TEST_CASE("wcslen") {
  constexpr const wchar_t str[] = L"How many characters does this string contain?";
  constexpr std::array<wchar_t, 7> char_array = {L'1', L'2', L'3', L'4', L'5', L'6', L'\0'};

  constexpr auto str_len = proposal::wcslen(str);
  static_assert(str_len == (std::size(str) - 1));
  REQUIRE(proposal::wcslen(str) == std::wcslen(str));

  constexpr auto char_array_len = proposal::wcslen(char_array.data());
  static_assert(char_array_len == (char_array.size() - 1));
  REQUIRE(proposal::wcslen(char_array.data()) == std::wcslen(char_array.data()));
}

TEST_CASE("wcscmp") {
  constexpr wchar_t str1[] = L"Hello, world!";
  constexpr wchar_t str2[] = L"Hello, everybody!";
  constexpr wchar_t str3[] = L"Hello, world!";

  static_assert(proposal::wcscmp(str1, str2) > 0);
  REQUIRE(is_same_signedness(proposal::wcscmp(str1, str2), std::wcscmp(str1, str2)));

  static_assert(proposal::wcscmp(str2, str3) < 0);
  REQUIRE(is_same_signedness(proposal::wcscmp(str2, str3), std::wcscmp(str2, str3)));

  static_assert(proposal::wcscmp(str1, str3) == 0);
  REQUIRE(is_same_signedness(proposal::wcscmp(str1, str3), std::wcscmp(str1, str3)));
}

TEST_CASE("wcsncmp") {
  constexpr wchar_t str1[] = L"Hello, world!";
  constexpr wchar_t str2[] = L"Hello, everybody!";

  static_assert(proposal::wcsncmp(str1, str2, 5) == 0);
  REQUIRE(is_same_signedness(proposal::wcsncmp(str1, str2, 5), std::wcsncmp(str1, str2, 5)));

  static_assert(proposal::wcsncmp(str1, str2, 10) > 0);
  REQUIRE(is_same_signedness(proposal::wcsncmp(str1, str2, 10), std::wcsncmp(str1, str2, 10)));

  static_assert(proposal::wcsncmp(str2, str1, 10) < 0);
  REQUIRE(is_same_signedness(proposal::wcsncmp(str2, str1, 10), std::wcsncmp(str2, str1, 10)));
}

TEST_CASE("wcschr") {
  auto test_strchr = []() constexpr {
    wchar_t str[] = L"Try not. Do, or do not. There is no try.";
    wchar_t target = 'D';
    return proposal::wcschr(str, target) != nullptr;
  };

  constexpr bool b = test_strchr();
  static_assert(b);

  wchar_t str[] = L"Try not. Do, or do not. There is no try.";
  wchar_t target = L'D';
  REQUIRE(proposal::wcschr(str, target) == std::wcschr(str, target));
}

TEST_CASE("const wcschr") {
  constexpr wchar_t str[] = L"Try not. Do, or do not. There is no try.";
  constexpr wchar_t target = L'D';
  static_assert(proposal::wcschr(str, target) != nullptr);
  REQUIRE(proposal::wcschr(str, target) == std::wcschr(str, target));
}

TEST_CASE("wcsrchr") {
  auto test_strrchr = []() constexpr {
    wchar_t str[] = L"/home/user/hello.c";
    wchar_t ch = L'/';
    return proposal::wcsrchr(str, ch) != nullptr;
  };

  constexpr bool b = test_strrchr();
  static_assert(b);

  wchar_t str[] = L"/home/user/hello.c";
  wchar_t ch = L'/';
  REQUIRE(proposal::wcsrchr(str, ch) == std::wcsrchr(str, ch));
}

TEST_CASE("const wcsrchr") {
  constexpr wchar_t str[] = L"/home/user/hello.c";
  constexpr wchar_t ch = L'/';
  static_assert(proposal::wcsrchr(str, ch) != nullptr);
  REQUIRE(proposal::wcsrchr(str, ch) == std::wcsrchr(str, ch));
}

TEST_CASE("wcsspn") {
  constexpr wchar_t low_alpha[] = L"qwertyuiopasdfghjklzxcvbnm";
  constexpr wchar_t str[]= L"abcde312$#@";
  static_assert(proposal::wcsspn(str, low_alpha) == 5);
  REQUIRE(proposal::wcsspn(str, low_alpha) == std::wcsspn(str, low_alpha));
}

TEST_CASE("wcscspn") {
  constexpr wchar_t invalid [] = L"*$#";
  constexpr wchar_t str[]= L"abcde312$#@";
  static_assert(proposal::wcscspn(str, invalid) == 8);
  REQUIRE(proposal::wcscspn(str, invalid) == std::wcscspn(str, invalid));
}

TEST_CASE("wcspbrk") {
  auto test_strpbrk = []() constexpr {
    wchar_t str[] = L"hello world, friend of mine!";
    wchar_t sep[] = L" ,!";
    return proposal::wcspbrk(str, sep) != nullptr;
  };

  constexpr bool b = test_strpbrk();
  static_assert(b);

  wchar_t str[] = L"hello world, friend of mine!";
  wchar_t sep[] = L" ,!";
  REQUIRE(proposal::wcspbrk(str, sep) == std::wcspbrk(str, sep));
}

TEST_CASE("const wcspbrk") {
  constexpr wchar_t str[] = L"hello world, friend of mine!";
  constexpr wchar_t sep[] = L" ,!";
  static_assert(proposal::wcspbrk(str, sep) != nullptr);
  REQUIRE(proposal::wcspbrk(str, sep) == std::wcspbrk(str, sep));
}

TEST_CASE("wcsstr") {
  auto test_strstr = []() constexpr {
    wchar_t str[] = L"Try not. Do, or do not. There is no try.";
    wchar_t target[] = L"not";
    return proposal::wcsstr(str, target) != nullptr;
  };

  constexpr bool b = test_strstr();
  static_assert(b);

  wchar_t str[] = L"Try not. Do, or do not. There is no try.";
  wchar_t target[] = L"not";
  REQUIRE(proposal::wcsstr(str, target) == std::wcsstr(str, target));
}

TEST_CASE("const wcsstr") {
  constexpr wchar_t str[] = L"Try not. Do, or do not. There is no try.";
  constexpr wchar_t target[] = L"not";
  static_assert(proposal::wcsstr(str, target) != nullptr);
  REQUIRE(proposal::wcsstr(str, target) == std::wcsstr(str, target));
}

TEST_CASE("wcstok") {
  auto test_wcstok = []() constexpr {
    wchar_t input[100] = L"A bird came down the walk";

    wchar_t str1[] = L"A";
    wchar_t str3[] = L"came";
    wchar_t str5[] = L"the";

    wchar_t* buffer = nullptr;
    wchar_t* token1 = proposal::wcstok(input, L" ", &buffer);
    (void)proposal::wcstok(nullptr, L" ", &buffer);
    wchar_t* token3 = proposal::wcstok(nullptr, L" ", &buffer);
    (void)proposal::wcstok(nullptr, L" ", &buffer);
    wchar_t* token5 = proposal::wcstok(nullptr, L" ", &buffer);

    return proposal::wcsncmp(str1, token1, proposal::wcslen(str1)) == 0 &&
           proposal::wcsncmp(str3, token3, proposal::wcslen(str3)) == 0 &&
           proposal::wcsncmp(str5, token5, proposal::wcslen(str5)) == 0;
  };

  constexpr bool b = test_wcstok();
  static_assert(b);
}

TEST_CASE("wmemchr") {
    auto test_memchr = []() constexpr {
    wchar_t arr[] = L"ABCDEFG";
    return proposal::wmemchr(arr, L'B', sizeof(arr)) != nullptr;
  };

  constexpr bool b = test_memchr();
  static_assert(b);

  wchar_t arr[] = L"ABCDEFG";
  REQUIRE(proposal::wmemchr(arr, L'D', sizeof(arr)) == std::wmemchr(arr, L'D', sizeof(arr)));
}

TEST_CASE("const wmemchr") {
  constexpr wchar_t arr[] = L"ABCDEFG";

  static_assert(proposal::wmemchr(arr, L'E', sizeof(arr)) != nullptr);
  REQUIRE(proposal::wmemchr(arr, L'E', sizeof(arr)) == std::wmemchr(arr, L'E', sizeof(arr)));
}

TEST_CASE("wmemcmp") {
  constexpr wchar_t str1[] = L"Hello, world!";
  constexpr wchar_t str2[] = L"Hello, everybody!";

  static_assert(proposal::wmemcmp(str1, str2, 5) == 0);
  REQUIRE(is_same_signedness(proposal::wmemcmp(str1, str2, 5), std::wmemcmp(str1, str2, 5)));

  static_assert(proposal::wmemcmp(str1, str2, 10) > 0);
  REQUIRE(is_same_signedness(proposal::wmemcmp(str1, str2, 10), std::wmemcmp(str1, str2, 10)));

  static_assert(proposal::wmemcmp(str2, str1, 10) < 0);
  REQUIRE(is_same_signedness(proposal::wmemcmp(str2, str1, 10), std::wmemcmp(str2, str1, 10)));
}

TEST_CASE("wmemset") {
  auto test_memset = [](wchar_t ch) constexpr {
    std::array<wchar_t, 10> m = {};
    proposal::wmemset(m.data(), ch, m.size());
    return m;
  };

  constexpr wchar_t ch = 1;
  constexpr auto m = test_memset(ch);
  for (auto i : m) {
    REQUIRE(i == ch);
  }
}

TEST_CASE("wmemcpy") {
  auto test_memcpy = [](const wchar_t* str) constexpr {
    std::array<wchar_t, 10> m = {};
    proposal::wmemcpy(m.data(), str, m.size());
    return m;
  };

  constexpr wchar_t str[] = L"Hello, world!";
  constexpr auto m = test_memcpy(str);
  static_assert(proposal::wcsncmp(str, m.data(), m.size()) == 0);
  REQUIRE(std::wcsncmp(str, m.data(), m.size()) == 0);
}

TEST_CASE("wmemmove") {
  //constexpr wchar_t str1[] = "1234567890";
  constexpr wchar_t str2[] = L"1234456890";

  auto test_memmove = []() constexpr {
    std::array<wchar_t, 10> m = {L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0'};
    proposal::wmemmove(m.data() + 4, m.data() + 3, 3);
    return m;
  };

  constexpr auto m = test_memmove();
  static_assert(proposal::wcsncmp(str2, m.data(), m.size()) == 0);
  REQUIRE(std::wcsncmp(str2, m.data(), m.size()) == 0);
}
