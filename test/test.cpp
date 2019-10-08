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
namespace proposal = nstd;

#include <array>
#include <cstring>
#include <iterator>

TEST_CASE("strcpy") {
  constexpr std::array<char, 7> char_array = {'1', '2', '3', '4', '5', '6', '\0'};
  auto test_strcpy = [](const char* str) constexpr {
    std::array<char, 32> m = {'\0'};
    proposal::strcpy(m.data(), str);
    return m;
  };

  constexpr auto char_array_cpy = test_strcpy(char_array.data());
  static_assert(proposal::strcmp(char_array_cpy.data(), char_array.data()) == 0);
  REQUIRE(std::strcmp(char_array_cpy.data(), char_array.data()) == 0);
}

TEST_CASE("strncpy") {
  constexpr std::array<char, 7> char_array = {'1', '2', '3', '4', '5', '6', '\0'};
  constexpr auto n = 5;
  auto test_strncpy = [](const char* str, std::size_t n) constexpr {
    std::array<char, 32> m = {'\0'};
    proposal::strncpy(m.data(), str, n);
    return m;
  };

  constexpr auto char_array_cpy = test_strncpy(char_array.data(), n);
  static_assert(proposal::strncmp(char_array_cpy.data(), char_array.data(), n) == 0);
  REQUIRE(std::strncmp(char_array_cpy.data(), char_array.data(), n) == 0);
}

TEST_CASE("strcat") {
}

TEST_CASE("strncat") {
}

TEST_CASE("strlen") {
  constexpr const char str[] = "How many characters does this string contain?";
  constexpr std::array<char, 7> char_array = {'1', '2', '3', '4', '5', '6', '\0'};

  constexpr auto str_len = proposal::strlen(str);
  static_assert(str_len == (std::size(str) - 1));
  REQUIRE(proposal::strlen(str) == std::strlen(str));

  constexpr auto char_array_len = proposal::strlen(char_array.data());
  static_assert(char_array_len == (char_array.size() - 1));
  REQUIRE(proposal::strlen(char_array.data()) == std::strlen(char_array.data()));
}

TEST_CASE("strcmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";
  constexpr char str3[] = "Hello, world!";

  static_assert(proposal::strcmp(str1, str2) > 0);
  REQUIRE(proposal::strcmp(str1, str2) == std::strcmp(str1, str2));

  static_assert(proposal::strcmp(str2, str3) < 0);
  REQUIRE(proposal::strcmp(str2, str3) == std::strcmp(str2, str3));

  static_assert(proposal::strcmp(str1, str3) == 0);
  REQUIRE(proposal::strcmp(str1, str3) == std::strcmp(str1, str3));
}

TEST_CASE("strncmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";

  static_assert(proposal::strncmp(str1, str2, 5) == 0);
  REQUIRE(proposal::strncmp(str1, str2, 5) == std::strncmp(str1, str2, 5));

  static_assert(proposal::strncmp(str1, str2, 10) > 0);
  REQUIRE(proposal::strncmp(str1, str2, 10) == std::strncmp(str1, str2, 10));

  static_assert(proposal::strncmp(str2, str1, 10) < 0);
  REQUIRE(proposal::strncmp(str2, str1, 10) == std::strncmp(str2, str1, 10));
}

TEST_CASE("strchr") {
}

TEST_CASE("const strchr") {
}

TEST_CASE("strrchr") {
}

TEST_CASE("const strrchr") {
}

TEST_CASE("strspn") {
}

TEST_CASE("strcspn") {
}

TEST_CASE("strpbrk") {
}

TEST_CASE("const strpbrk") {
}

TEST_CASE("strstr") {
}

TEST_CASE("const strstr") {
}

#if defined(__clang__)
TEST_CASE("memchr") {
}

TEST_CASE("const memchr") {
  constexpr char arr[] = {'a','\0','a','A','a','a','A','a'};

  static_assert(proposal::memchr(arr, 'A', sizeof(arr)) != nullptr);
  REQUIRE(proposal::memchr(arr, 'A', sizeof(arr)) == std::memchr(arr, 'A', sizeof(arr)));
}
#endif

#if defined(__clang__) || defined(_MSC_VER)
TEST_CASE("memcmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";

  static_assert(proposal::memcmp(str1, str2, 5) == 0);
  REQUIRE(proposal::memcmp(str1, str2, 5) == std::memcmp(str1, str2, 5));

  static_assert(proposal::memcmp(str1, str2, 10) > 0);
  REQUIRE(proposal::memcmp(str1, str2, 10) == std::memcmp(str1, str2, 10));

  static_assert(proposal::memcmp(str2, str1, 10) < 0);
  REQUIRE(proposal::memcmp(str2, str1, 10) == std::memcmp(str2, str1, 10));
}
#endif

#if 0
// clang error: constexpr variable 'm' must be initialized by a constant expression constexpr auto m = test_memset(ch);
// note: subexpression not valid in a constant expression return __builtin_memset(dest, ch, count);
TEST_CASE("memset") {
  auto test_memset = [](int ch) constexpr {
    std::array<int, 10> m = {};
    proposal::memset(m.data(), ch, m.size());
    return m;
  };

  constexpr int ch = 1;
  constexpr auto m = test_memset(ch);
  for (auto i : m) {
    REQUIRE(i == ch);
  }
}
#endif

#if defined(__clang__)
TEST_CASE("memcpy") {
  auto test_memcpy = [](const char* str) constexpr {
    std::array<char, 10> m = {};
    proposal::memcpy(m.data(), str, m.size());
    return m;
  };

  constexpr char str[] = "Hello, world!";
  constexpr auto m = test_memcpy(str);
  static_assert(proposal::strncmp(str, m.data(), m.size()) == 0);
  REQUIRE(std::strncmp(str, m.data(), m.size()) == 0);
}
#endif

#if defined(__clang__)
TEST_CASE("memmove") {
  //constexpr char str1[] = "1234567890";
  constexpr char str2[] = "1234456890";

  auto test_memmove = []() constexpr {
    std::array<char, 10> m = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    proposal::memmove(m.data() + 4, m.data() + 3, 3);
    return m;
  };

  constexpr auto m = test_memmove();
  static_assert(proposal::strncmp(str2, m.data(), m.size()) == 0);
  REQUIRE(std::strncmp(str2, m.data(), m.size()) == 0);
}
#endif
