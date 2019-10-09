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

TEST_CASE("strcpy") {
  constexpr std::array<char, 7> char_array = {'1', '2', '3', '4', '5', '6', '\0'};
  auto test_strcpy = [](const char* str) constexpr {
    std::array<char, 32> m = {};
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
    std::array<char, 32> m = {};
    proposal::strncpy(m.data(), str, n);
    return m;
  };

  constexpr auto char_array_cpy = test_strncpy(char_array.data(), n);
  static_assert(proposal::strncmp(char_array_cpy.data(), char_array.data(), n) == 0);
  REQUIRE(std::strncmp(char_array_cpy.data(), char_array.data(), n) == 0);
}

TEST_CASE("strcat") {
  auto test_strcat = []() constexpr {
    char str1[50] = "Hello ";
    char str2[50] = "World!";
    proposal::strcat(str1, str2);
    return proposal::strcmp(str1, "Hello World!") == 0;
  };

  constexpr bool b = test_strcat();
  static_assert(b);
}

TEST_CASE("strncat") {
  auto test_strncat = []() constexpr {
    const std::size_t n = 3;
    char str1[50] = "Hello ";
    char str2[50] = "World!";
    proposal::strncat(str1, str2, n);
    return proposal::strncmp(str1, "Hello World!", proposal::strlen(str1)) == 0;
  };

  constexpr bool b = test_strncat();
  static_assert(b);
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
  REQUIRE(is_same_signedness(proposal::strcmp(str1, str2), std::strcmp(str1, str2)));

  static_assert(proposal::strcmp(str2, str3) < 0);
  REQUIRE(is_same_signedness(proposal::strcmp(str2, str3), std::strcmp(str2, str3)));

  static_assert(proposal::strcmp(str1, str3) == 0);
  REQUIRE(is_same_signedness(proposal::strcmp(str1, str3), std::strcmp(str1, str3)));
}

TEST_CASE("strncmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";

  static_assert(proposal::strncmp(str1, str2, 5) == 0);
  REQUIRE(is_same_signedness(proposal::strncmp(str1, str2, 5), std::strncmp(str1, str2, 5)));

  static_assert(proposal::strncmp(str1, str2, 10) > 0);
  REQUIRE(is_same_signedness(proposal::strncmp(str1, str2, 10), std::strncmp(str1, str2, 10)));

  static_assert(proposal::strncmp(str2, str1, 10) < 0);
  REQUIRE(is_same_signedness(proposal::strncmp(str2, str1, 10), std::strncmp(str2, str1, 10)));
}

TEST_CASE("strchr") {
  auto test_strchr = []() constexpr {
    char str[] = "Try not. Do, or do not. There is no try.";
    char target = 'D';
    return proposal::strchr(str, target) != nullptr;
  };

  constexpr bool b = test_strchr();
  static_assert(b);

  char str[] = "Try not. Do, or do not. There is no try.";
  char target = 'D';
  REQUIRE(proposal::strchr(str, target) == std::strchr(str, target));
}

TEST_CASE("const strchr") {
  constexpr char str[] = "Try not. Do, or do not. There is no try.";
  constexpr char target = 'D';
  static_assert(proposal::strchr(str, target) != nullptr);
  REQUIRE(proposal::strchr(str, target) == std::strchr(str, target));
}

TEST_CASE("strrchr") {
  auto test_strrchr = []() constexpr {
    char str[] = "/home/user/hello.c";
    char ch = '/';
    return proposal::strrchr(str, ch) != nullptr;
  };

  constexpr bool b = test_strrchr();
  static_assert(b);

  char str[] = "/home/user/hello.c";
  char ch = '/';
  REQUIRE(proposal::strrchr(str, ch) == std::strrchr(str, ch));
}

TEST_CASE("const strrchr") {
  constexpr char str[] = "/home/user/hello.c";
  constexpr char ch = '/';
  static_assert(proposal::strrchr(str, ch) != nullptr);
  REQUIRE(proposal::strrchr(str, ch) == std::strrchr(str, ch));
}

TEST_CASE("strspn") {
  constexpr char low_alpha[] = "qwertyuiopasdfghjklzxcvbnm";
  constexpr char str[]= "abcde312$#@";
  static_assert(proposal::strspn(str, low_alpha) == 5);
  REQUIRE(proposal::strspn(str, low_alpha) == std::strspn(str, low_alpha));
}

TEST_CASE("strcspn") {
  constexpr char invalid [] = "*$#";
  constexpr char str[]= "abcde312$#@";
  static_assert(proposal::strcspn(str, invalid) == 8);
  REQUIRE(proposal::strcspn(str, invalid) == std::strcspn(str, invalid));
}

TEST_CASE("strpbrk") {
  auto test_strpbrk = []() constexpr {
    char str[] = "hello world, friend of mine!";
    char sep[] = " ,!";
    return proposal::strpbrk(str, sep) != nullptr;
  };

  constexpr bool b = test_strpbrk();
  static_assert(b);

  char str[] = "hello world, friend of mine!";
  char sep[] = " ,!";
  REQUIRE(proposal::strpbrk(str, sep) == std::strpbrk(str, sep));
}

TEST_CASE("const strpbrk") {
  constexpr char str[] = "hello world, friend of mine!";
  constexpr char sep[] = " ,!";
  static_assert(proposal::strpbrk(str, sep) != nullptr);
  REQUIRE(proposal::strpbrk(str, sep) == std::strpbrk(str, sep));
}

TEST_CASE("strstr") {
  auto test_strstr = []() constexpr {
    char str[] = "Try not. Do, or do not. There is no try.";
    char target[] = "not";
    return proposal::strstr(str, target) != nullptr;
  };

  constexpr bool b = test_strstr();
  static_assert(b);

  char str[] = "Try not. Do, or do not. There is no try.";
  char target[] = "not";
  REQUIRE(proposal::strstr(str, target) == std::strstr(str, target));
}

TEST_CASE("const strstr") {
  constexpr char str[] = "Try not. Do, or do not. There is no try.";
  constexpr char target[] = "not";
  static_assert(proposal::strstr(str, target) != nullptr);
  REQUIRE(proposal::strstr(str, target) == std::strstr(str, target));
}

TEST_CASE("strtok") {
}

#if defined(__clang__)
TEST_CASE("memchr") {
    auto test_memchr = []() constexpr {
    char arr[] = "ABCDEFG";
    return proposal::memchr(arr, 'B', sizeof(arr)) != nullptr;
  };

  constexpr bool b = test_memchr();
  static_assert(b);

  char arr[] = "ABCDEFG";
  REQUIRE(proposal::memchr(arr, 'D', sizeof(arr)) == std::memchr(arr, 'D', sizeof(arr)));
}

TEST_CASE("const memchr") {
  constexpr char arr[] = "ABCDEFG";

  static_assert(proposal::memchr(arr, 'E', sizeof(arr)) != nullptr);
  REQUIRE(proposal::memchr(arr, 'E', sizeof(arr)) == std::memchr(arr, 'E', sizeof(arr)));
}
#endif

#if defined(__clang__) || defined(_MSC_VER)
TEST_CASE("memcmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";

  static_assert(proposal::memcmp(str1, str2, 5) == 0);
  REQUIRE(is_same_signedness(proposal::memcmp(str1, str2, 5), std::memcmp(str1, str2, 5)));

  static_assert(proposal::memcmp(str1, str2, 10) > 0);
  REQUIRE(is_same_signedness(proposal::memcmp(str1, str2, 10), std::memcmp(str1, str2, 10)));

  static_assert(proposal::memcmp(str2, str1, 10) < 0);
  REQUIRE(is_same_signedness(proposal::memcmp(str2, str1, 10), std::memcmp(str2, str1, 10)));
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
