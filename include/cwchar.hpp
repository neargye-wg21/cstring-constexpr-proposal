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

#pragma once

#include <cstddef> // NULL, size_t
#include <cwchar>
#include "detail.hpp"

namespace nstd {

#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4996)
#endif

constexpr wchar_t* wcscpy(wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && src != nullptr) {
      wchar_t* d = dest;
      for (; (*d = *src) != L'\0'; ++d, ++src) {
      }
    }

    return dest;
  } else {
    return std::wcscpy(dest, src);
  }
}

constexpr wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && src != nullptr && count != 0) {
      wchar_t* d = dest;
      do {
        if ((*d++ = *src++) == L'\0') {
          while (--count != 0) {
            *d++ = L'\0';
          }
          break;
        }
      } while (--count != 0);
    }

    return dest;
  } else {
    return std::wcsncpy(dest, src, count);
  }
}

constexpr wchar_t* wcscat(wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && src != nullptr) {
      wchar_t* d = dest;
      for (; *d != L'\0'; ++d) {
      }
      while ((*d++ = *src++) != L'\0') {
      }
    }

    return dest;
  } else {
    return std::wcscat(dest, src);
  }
}

constexpr wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && src != nullptr && count != 0) {
      wchar_t* d = dest;
      for (; *d != L'\0'; ++d) {
      }
      do {
        if ((*d = *src++) == L'\0') {
          break;
        }
        d++;
      } while (--count != 0);
      *d = L'\0';
    }

    return dest;
  } else {
    return std::wcsncat(dest, src, count);
  }
}

constexpr std::size_t wcslen(const wchar_t* str) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__)
    std::size_t i = 0;
    if (str != nullptr) {
      while (str[i] != L'\0') {
        ++i;
      }
    }

    return i;
#elif defined(__clang__) || defined(_MSC_VER)
    return __builtin_wcslen(str);
#endif
  } else {
    return std::wcslen(str);
  }
}

constexpr int wcscmp(const wchar_t* lhs, const wchar_t* rhs) noexcept {
  if (detail::is_constant_evaluated()) {
    if (lhs == nullptr || rhs == nullptr) {
      return rhs != nullptr ? -1 : 1;
    }

    while (*lhs == *rhs++) {
      if (*lhs++ == L'\0') {
        return 0;
      }
    }

    return static_cast<unsigned int>(*lhs) -static_cast<unsigned int>(*(rhs - 1));
  } else {
    return std::wcscmp(lhs, rhs);
  }
}

constexpr int wcsncmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__)
    if (lhs == nullptr || rhs == nullptr) {
      return rhs != nullptr ? -1 : 1;
    }

    for (std::size_t i = 0; i < count; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      } else if (lhs[i] == L'\0') {
        return 0;
      }
    }

    return 0;
#elif defined(__clang__) || defined(_MSC_VER)
    return __builtin_wmemcmp(lhs, rhs, count);
#endif
  } else {
    return std::wcsncmp(lhs, rhs, count);
  }
}

constexpr const wchar_t* wcschr(const wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    if (str != nullptr) {
      for (std::size_t i = 0; str[i] != L'\0'; ++i) {
        if (str[i] == ch) {
          return &str[i];
        }
      }
    }

    return nullptr;
  } else {
    return std::wcschr(str, ch);
  }
}

constexpr wchar_t* wcschr(wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    if (str != nullptr) {
      for (std::size_t i = 0; str[i] != L'\0'; ++i) {
        if (str[i] == ch) {
          return &str[i];
        }
      }
    }

    return nullptr;
  } else {
    return std::wcschr(str, ch);
  }
}

constexpr const wchar_t* wcsrchr(const wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    int p = -1;
    if (str != nullptr) {
      for (std::size_t i = 0; str[i] != L'\0'; ++i) {
        if (str[i] == ch) {
          p = i;
        }
      }
    }

    return p != -1 ? &str[p] : nullptr;
  } else {
    return std::wcsrchr(str, ch);
  }
}

constexpr wchar_t* wcsrchr(wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    int p = -1;
    if (str != nullptr) {
      for (std::size_t i = 0; str[i] != L'\0'; ++i) {
        if (str[i] == ch) {
          p = i;
        }
      }
    }

    return p != -1 ? &str[p] : nullptr;
  } else {
    return std::wcsrchr(str, ch);
  }
}

constexpr std::size_t wcsspn(const wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    std::size_t i = 0;
    if (dest != nullptr) {
      while (dest[i] != L'\0' && wcsrchr(src, dest[i]) != nullptr) {
        ++i;
      }
    }

    return i;
  } else {
    return std::wcsspn(dest, src);
  }
}

constexpr std::size_t wcscspn(const wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    std::size_t i = 0;
    if (dest != nullptr) {
      while (dest[i] != L'\0' && wcsrchr(src, dest[i]) == nullptr) {
        ++i;
      }
    }

    return i;
  } else {
    return std::wcscspn(dest, src);
  }
}

constexpr const wchar_t* wcspbrk(const wchar_t* dest, const wchar_t* breakset) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && breakset != nullptr) {
      for (std::size_t i = 0; dest[i] != L'\0'; ++i) {
        if (wcschr(breakset, dest[i]) != nullptr) {
          return &dest[i];
        }
      }
    }

    return nullptr;
  } else {
    return std::wcspbrk(dest, breakset);
  }
}

constexpr wchar_t* wcspbrk(wchar_t* dest, const wchar_t* breakset) noexcept {
  if (detail::is_constant_evaluated()) {
    if (dest != nullptr && breakset != nullptr) {
      for (std::size_t i = 0; dest[i] != L'\0'; ++i) {
        if (wcschr(breakset, dest[i]) != nullptr) {
          return &dest[i];
        }
      }
    }

    return nullptr;
  } else {
    return std::wcspbrk(dest, breakset);
  }
}

constexpr const wchar_t* wcsstr(const wchar_t* str, const wchar_t* target) noexcept {
  if (detail::is_constant_evaluated()) {
    if (wchar_t c = target != nullptr ? *target++ : L'\0'; c != L'\0' && str != nullptr) {
      std::size_t len = wcslen(target);
      do {
        wchar_t sc = {};
        do {
          if ((sc = *str++) == L'\0') {
            return nullptr;
          }
        } while (sc != c);
      } while (wcsncmp(str, target, len) != 0);
      --str;
    }

    return str;
  } else {
    return std::wcsstr(str, target);
  }
}

constexpr wchar_t* wcsstr(wchar_t* str, const wchar_t* target) noexcept {
  if (detail::is_constant_evaluated()) {
    if (wchar_t c = target != nullptr ? *target++ : L'\0'; c != L'\0' && str != nullptr) {
      std::size_t len = wcslen(target);
      do {
        wchar_t sc = {};
        do {
          if ((sc = *str++) == L'\0') {
            return nullptr;
          }
        } while (sc != c);
      } while (wcsncmp(str, target, len) != 0);
      --str;
    }

    return str;
  } else {
    return std::wcsstr(str, target);
  }
}

constexpr wchar_t* wcstok(wchar_t* str, const wchar_t* delim, wchar_t** ptr) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER) || defined(__clang__)
    if (str == nullptr && (str = *ptr) == nullptr) {
      return nullptr;
    }

    str += wcsspn(str, delim);
    if (*str == L'\0') {
      return *ptr = nullptr;
    }

    *ptr = str + wcscspn(str, delim);
    if (**ptr != L'\0') {
      *(*ptr)++ = L'\0';
    } else {
      *ptr = nullptr;
    }

    return str;
#endif
  } else {
    return std::wcstok(str, delim, ptr);
  }
}

constexpr wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER)
    if (dest != nullptr && src != nullptr && count != 0) {
      for (std::size_t i = 0; i < count; ++i) {
        dest[i] = src[i];
      }
    }

    return dest;
#elif defined(__clang__)
    return __builtin_wmemcpy(dest, src, count);
#endif
  } else {
    return std::wmemcpy(dest, src, count);
  }
}

constexpr wchar_t* wmemmove(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER)
    if (dest != nullptr && src != nullptr && count != 0) {
      wchar_t* d = dest;
      if (dest > src) {
        const wchar_t* s = src + count;
        d += count;
        for (; count; --count) {
          *(--d) = *(--s);
        }
      } else if (dest < src) {
        for (; count; --count) {
          *(d++) = *(src++);
        }
      }
    }

    return dest;
#elif defined(__clang__)
    return __builtin_wmemmove(dest, src, count);
#endif
  } else {
    return std::wmemmove(dest, src, count);
  }
}

constexpr int wmemcmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__)
    if (lhs != nullptr && rhs != nullptr && count != 0) {
      for (std::size_t i = 0; i < count; ++i) {
        if (lhs[i] != rhs[i]) {
          return lhs[i] < rhs[i] ? -1 : 1;
        }
      }
    }

    return 0;
#elif defined(__clang__) || defined(_MSC_VER)
    return __builtin_wmemcmp(lhs, rhs, count);
#endif
  } else {
    return std::wmemcmp(lhs, rhs, count);
  }
}

constexpr const wchar_t* wmemchr(const wchar_t* ptr, wchar_t ch, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER)
    if (ptr != nullptr && count != 0) {
      for (std::size_t i = 0; i < count; ++i) {
        if (ptr[i] == ch) {
          return &ptr[i];
        }
      }
    }

    return nullptr;
#elif defined(__clang__)
    return __builtin_wmemchr(ptr, ch, count);
#endif
  } else {
    return std::wmemchr(ptr, ch, count);
  }
}

constexpr wchar_t* wmemchr(wchar_t* ptr, wchar_t ch, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER)
    if (ptr != nullptr && count != 0) {
      for (std::size_t i = 0; i < count; ++i) {
        if (ptr[i] == ch) {
          return &ptr[i];
        }
      }
    }

    return nullptr;
#elif defined(__clang__)
    return __builtin_wmemchr(ptr, ch, count);
#endif
  } else {
    return std::wmemchr(ptr, ch, count);
  }
}

constexpr wchar_t* wmemset(wchar_t* dest, wchar_t ch, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
  // clang no __builtin_memset ?
#if defined(__GNUC__) && !defined(__clang__) || defined(_MSC_VER) || defined(__clang__)
    if (dest != nullptr && count != 0) {
      for (std::size_t i = 0; i < count; ++i) {
        dest[i] = ch;
      }
    }

    return dest;
#endif
  } else {
    return std::wmemset(dest, ch, count);
  }
}

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

} // namespace nstd
