#include <cstddef> // NULL, size_t
#include <algorithm> // min, copy
#include <cstring>
#include <type_traits> // is_constant_evaluated

namespace nstd {

#if defined(__clang__)
#  define nstd_CLANG
#elif defined(_MSC_VER)
#  define nstd_MSVC
#elif defined(__GNUC__)
#  define nstd_GCC
#endif

#if defined(nstd_GCC)
constexpr bool is_constant_evaluated() {
  return std::is_constant_evaluated();
}
#elif defined(nstd_MSVC) || defined(nstd_CLANG)
// Not support std::is_constant_evaluated() yet.
constexpr bool is_constant_evaluated() {
  return true;
}
#endif

constexpr char* strcpy(char* dest, const char* src) noexcept {
  if (is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strcpy.c
    char* d = dest;

    for (; (*d = *src) != '\0'; ++d, ++src) {
    }

    return dest;
  }

  return std::strcpy(dest, src);
}

constexpr char* strncpy(char* dest, const char* src, std::size_t count) noexcept {
  if (is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strncpy.c
    if (count != 0) {
      char* d = dest;

      do {
        if ((*d++ = *src++) == '\0') {
          while (--count != 0) {
            *d++ = '\0';
          }
          break;
        }
      } while (--count != 0);
    }

    return dest;
  }

  return std::strncpy(dest, src, count);
}

constexpr char* strcat(char* dest, const char* src) noexcept {
  if (is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strcat.c
    char* d = dest;

    for (; *d; ++d) {
    }
    while ((*d++ = *src++) != '\0') {
    }

    return dest;
  }

  return std::strcat(dest, src);
}

constexpr char* strncat(char* dest, const char* src, std::size_t count) noexcept {
  if (is_constant_evaluated()) {
    // https://github.com/freebsd/freebsd/blob/master/sys/libkern/strncat.c
    if (count != 0) {
      char* d = dest;

      while (*d != '\0') {
        d++;
      }
      do {
        if ((*d = *src++) == '\0') {
          break;
        }
        d++;
      } while (--count != 0);
      *d = '\0';
    }

    return dest;
  }

  return std::strncat(dest, src, count);
}

// constexpr work with a locale requires constexpr locale.
std::size_t strxfrm(char* dest, const char* src, std::size_t count) noexcept {
  return std::strxfrm(dest, src, count);
}

constexpr std::size_t strlen(const char* str) noexcept {
  if (is_constant_evaluated()) {
#if defined(nstd_GCC)
    // https://github.com/gcc-mirror/gcc/blob/5c7634a0e5f202935aa6c11b6ea953b8bf80a00a/libstdc%2B%2B-v3/include/bits/char_traits.h#L329
    std::size_t i = 0;
    while (str[i] != '\0') {
      ++i;
    }

    return i;
#elif defined(nstd_CLANG) || defined(nstd_MSVC)
    return __builtin_strlen(str);
#endif
  }

  return std::strlen(str);
}

constexpr int strcmp(const char* lhs, const char* rhs) noexcept {
  if (is_constant_evaluated()) {
    // https://github.com/microsoft/STL/blob/cd8fee03209d3312bf3c79abf81371290f116d84/stl/inc/xstring#L513
    const std::size_t lhs_len = strlen(lhs);
    const std::size_t rhs_len = strlen(rhs);
    const std::size_t len = std::min(lhs_len, rhs_len);
#if defined(nstd_GCC)
    // https://github.com/gcc-mirror/gcc/blob/13b9cbfc32fe3ac4c81c4dd9c42d141c8fb95db4/libstdc%2B%2B-v3/include/bits/char_traits.h#L655
    for (std::size_t i = 0; i < len; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      } else if (lhs[i] == '\0') {
        return 0;
      }
    }
#elif defined(nstd_MSVC) || defined(nstd_CLANG)
    if (const int ans = __builtin_memcmp(lhs, rhs, len); ans != 0) {
      return ans;
    }
#endif
    if (lhs_len != rhs_len) {
      return lhs_len < rhs_len ? -1 : 1;
    }

    return 0;
  }

  return std::strcmp(lhs, rhs);
}

constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept {
  if (is_constant_evaluated()) {
#if defined(nstd_GCC)
    // https://github.com/gcc-mirror/gcc/blob/13b9cbfc32fe3ac4c81c4dd9c42d141c8fb95db4/libstdc%2B%2B-v3/include/bits/char_traits.h#L655
    for (std::size_t i = 0; i < count; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      } else if (lhs[i] == '\0') {
        return 0;
      }
    }

    return 0;
#elif defined(nstd_MSVC) || defined(nstd_CLANG)
    return __builtin_memcmp(lhs, rhs, count);
#endif
  }

  return std::strncmp(lhs, rhs, count);
}

// constexpr work with a locale requires constexpr locale.
int strcoll(const char* lhs, const char* rhs) noexcept {
  return std::strcoll(lhs, rhs);
}

constexpr const char* strchr(const char* str, int ch) noexcept {
  if (is_constant_evaluated()) {
    for (std::size_t i = 0;; ++i) {
      if (str[i] == ch) {
        return &str[i];
      } else if (str[i] == '\0') {
        return nullptr;
      }
    }
  }

  return std::strchr(str, ch);
}

constexpr char* strchr(char* str, int ch) noexcept {
  if (is_constant_evaluated()) {
    for (std::size_t i = 0;; ++i) {
      if (str[i] == ch) {
        return &str[i];
      } else if (str[i] == '\0') {
        return nullptr;
      }
    }
  }

  return std::strchr(str, ch);
}

constexpr const char* strrchr(const char* str, int ch) noexcept {
  if (is_constant_evaluated()) {
    int p = -1;
    for (std::size_t i = 0;; ++i) {
      if (str[i] == ch) {
        p = i;
      } else if (str[i] == '\0') {
        return p != -1 ? &str[p] : nullptr;
      }
    }
  }

  return std::strrchr(str, ch);
}

constexpr char* strrchr(char* str, int ch) noexcept {
  if (is_constant_evaluated()) {
    char* p = nullptr;
    for (std::size_t i = 0;; ++i) {
      if (str[i] == ch) {
        p = &str[i];
      } else if (str[i] == '\0') {
        return p;
      }
    }
  }

  return std::strrchr(str, ch);
}

constexpr std::size_t strspn(const char* dest, const char* src) noexcept {
  if (is_constant_evaluated()) {
    return 0; //TODO
  }

  return std::strspn(dest, src);
}

constexpr std:: size_t strcspn(const char* dest, const char* src) noexcept {
  if (is_constant_evaluated()) {
    return 0; //TODO
  }

  return std::strcspn(dest, src);
}

constexpr int memcmp(const void* lhs, const void* rhs, std::size_t count) noexcept {
  if (is_constant_evaluated()) {
#if defined(nstd_GCC)
    (void)lhs;
    (void)rhs;
    (void)count;
    return 0; //TODO
#elif defined(nstd_CLANG) || defined(nstd_MSVC)
    return __builtin_memcmp(lhs, rhs, count);
#endif
  }

  return std::memcmp(lhs, rhs, count);
}


// System error code non constexpr context.
char* strerror(int errnum) noexcept {
  return std::strerror(errnum);
}

} // namespace nstd
