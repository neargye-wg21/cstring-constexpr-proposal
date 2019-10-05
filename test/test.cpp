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

#include <array>
#include <cstring>
#include <iterator>

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

TEST_CASE("strcmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";
  constexpr char str3[] = "Hello, world!";

  static_assert(proposal::strcmp(str1, str2) > 0);
  REQUIRE(proposal::strcmp(str1, str2) > 0);

  static_assert(proposal::strcmp(str2, str3) < 0);
  REQUIRE(proposal::strcmp(str2, str3) < 0);

  static_assert(proposal::strcmp(str1, str3) == 0);
  REQUIRE(proposal::strcmp(str1, str3) == 0);
}

TEST_CASE("strncmp") {
  constexpr char str1[] = "Hello, world!";
  constexpr char str2[] = "Hello, everybody!";

  static_assert(proposal::strncmp(str1, str2, 5) == 0);
  REQUIRE(proposal::strncmp(str1, str2, 5) == 0);

  static_assert(proposal::strncmp(str1, str2, 10) > 0);
  REQUIRE(proposal::strncmp(str1, str2, 10) > 0);

  static_assert(proposal::strncmp(str2, str1, 10) < 0);
  REQUIRE(proposal::strncmp(str2, str1, 10) < 0);
}
