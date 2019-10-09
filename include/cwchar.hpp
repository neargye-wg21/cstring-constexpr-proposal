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
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strcpy.c
    wchar_t* d = dest;

    for (; (*d = *src) != L'\0'; ++d, ++src) {
    }

    return dest;
  } else {
    return std::wcscpy(dest, src);
  }
}

constexpr wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strncpy.c
    if (count != 0) {
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
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strcat.c
    wchar_t* d = dest;

    for (; *d != L'\0'; ++d) {
    }
    while ((*d++ = *src++) != L'\0') {
    }

    return dest;
  } else {
    return std::wcscat(dest, src);
  }
}

constexpr wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strncat.c
    if (count != 0) {
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

// constexpr work with a locale requires constexpr locale.
std::size_t wcsxfrm(wchar_t* dest, const wchar_t* src, std::size_t count) noexcept {
  return std::wcsxfrm(dest, src, count);
}

constexpr std::size_t wcslen(const wchar_t* str) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__)
    // https://github.com/gcc-mirror/gcc/blob/5c7634a0e5f202935aa6c11b6ea953b8bf80a00a/libstdc%2B%2B-v3/include/bits/char_traits.h#L329
    std::size_t i = 0;
    while (str[i] != L'\0') {
      ++i;
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
    // https://github.com/microsoft/STL/blob/cd8fee03209d3312bf3c79abf81371290f116d84/stl/inc/xstring#L513
    const std::size_t lhs_len = wcslen(lhs);
    const std::size_t rhs_len = wcslen(rhs);
    const std::size_t len = lhs_len < rhs_len ? lhs_len : rhs_len; // min(lhs_len, rhs_len)
#if defined(__GNUC__) && !defined(__clang__)
    // https://github.com/gcc-mirror/gcc/blob/13b9cbfc32fe3ac4c81c4dd9c42d141c8fb95db4/libstdc%2B%2B-v3/include/bits/char_traits.h#L655
    for (std::size_t i = 0; i < len; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      }
    }
#elif defined(__clang__) || defined(_MSC_VER)
    if (const int ans = __builtin_wmemcmp(lhs, rhs, len); ans != 0) {
      return ans;
    }
#endif
    if (lhs_len != rhs_len) {
      return lhs_len < rhs_len ? -1 : 1;
    }

    return 0;
  } else {
    return std::wcscmp(lhs, rhs);
  }
}

constexpr int wcsncmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count) noexcept {
  if (detail::is_constant_evaluated()) {
#if defined(__GNUC__) && !defined(__clang__)
    // https://github.com/gcc-mirror/gcc/blob/13b9cbfc32fe3ac4c81c4dd9c42d141c8fb95db4/libstdc%2B%2B-v3/include/bits/char_traits.h#L655
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

// constexpr work with a locale requires constexpr locale.
int wcscoll(const wchar_t* lhs, const wchar_t* rhs) noexcept {
  return std::wcscoll(lhs, rhs);
}

constexpr const wchar_t* wcschr(const wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    for (std::size_t i = 0; str[i] != L'\0'; ++i) {
      if (str[i] == ch) {
        return &str[i];
      }
    }

    return nullptr;
  } else {
    return std::wcschr(str, ch);
  }
}

constexpr wchar_t* wcschr(wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    for (std::size_t i = 0; str[i] != L'\0'; ++i) {
      if (str[i] == ch) {
        return &str[i];
      }
    }

    return nullptr;
  } else {
    return std::wcschr(str, ch);
  }
}

constexpr const wchar_t* wcsrchr(const wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    int p = -1;
    for (std::size_t i = 0; str[i] != L'\0'; ++i) {
      if (str[i] == ch) {
        p = i;
      }
    }

    return p != -1 ? &str[p] : nullptr;
  } else {
    return std::wcsrchr(str, ch);
  }
}

constexpr wchar_t* wcsrchr(wchar_t* str, wchar_t ch) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    int p = -1;
    for (std::size_t i = 0; str[i] != L'\0'; ++i) {
      if (str[i] == ch) {
        p = i;
      }
    }

    return p != -1 ? &str[p] : nullptr;
  } else {
    return std::wcsrchr(str, ch);
  }
}

constexpr std::size_t wcsspn(const wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    std::size_t i = 0;
    while (dest[i] != L'\0' && wcsrchr(src, dest[i]) != nullptr) {
      ++i;
    }

    return i;
  } else {
    return std::wcsspn(dest, src);
  }
}

constexpr std::size_t wcscspn(const wchar_t* dest, const wchar_t* src) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    std::size_t i = 0;
    while (dest[i] != L'\0' && wcsrchr(src, dest[i]) == nullptr) {
      ++i;
    }

    return i;
  } else {
    return std::wcscspn(dest, src);
  }
}

constexpr const wchar_t* wcspbrk(const wchar_t* dest, const wchar_t* breakset) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    for (std::size_t i = 0; dest[i] != L'\0'; ++i) {
      if (wcschr(breakset, dest[i]) != nullptr) {
        return &dest[i];
      }
    }

    return nullptr;
  } else {
    return std::wcspbrk(dest, breakset);
  }
}

constexpr wchar_t* wcspbrk(wchar_t* dest, const wchar_t* breakset) noexcept {
  if (detail::is_constant_evaluated()) {
    // Naive implementation.
    for (std::size_t i = 0; dest[i] != L'\0'; ++i) {
      if (wcschr(breakset, dest[i]) != nullptr) {
        return &dest[i];
      }
    }

    return nullptr;
  } else {
    return std::wcspbrk(dest, breakset);
  }
}

constexpr const wchar_t* wcsstr(const wchar_t* str, const wchar_t* target) noexcept {
  if (detail::is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strstr.c
    if (wchar_t c = *target++; c != L'\0') {
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
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strstr.c
    if (wchar_t c = *target++; c != L'\0') {
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
    // Naive implementation.
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
    // Naive implementation.
    if (dest != nullptr && src != nullptr) {
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
    // Naive implementation.
    if (dest != nullptr && src != nullptr) {
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
    // Naive implementation.
    if (dest != nullptr && src != nullptr) {
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
    // Naive implementation.
    if (ptr != nullptr) {
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
    // Naive implementation.
    if (ptr != nullptr) {
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
    // Naive implementation.
    if (dest != nullptr) {
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
