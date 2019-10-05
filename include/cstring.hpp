#include <cstddef> // NULL, size_t
#include <algorithm> // min, copy
#include <cstring>
#include <type_traits> // is_constant_evaluated

namespace proposal {

constexpr std::size_t strlen(const char* str) noexcept {
#if defined(__clang__) || defined(_MSC_VER)
  return __builtin_strlen(str);
#elif defined(__GNUC__)
  // gcc-9 error: __builtin_strlen is not a constant expression!
  if (std::is_constant_evaluated()) {
    std::size_t i = 0;
    while (str[i] != '\0') {
      ++i;
    }

    return i;
  } else {
    return std::strlen(str);
  }
#endif
}

constexpr char* strncpy(char* dest, const char* src, std::size_t count) noexcept {
#if 0 // when std::copy will constexpr and will suport std::is_constant_evaluated.
  if (std::is_constant_evaluated()) {
    std::copy(src, src + count, dest);

    return dest;
  } else {
    return std::strncpy(dest, src, count);
  }
#elif defined(__clang__) || defined(_MSC_VER)
  for (std::size_t i = 0; i < count; ++i) {
    if (src[i] == '\0') {
      break;
    }
    dest[i] = src[i];
  }

  return dest;
#elif defined(__GNUC__)
  if (std::is_constant_evaluated()) {
    for (std::size_t i = 0; i < count; ++i) {
      if (src[i] == '\0') {
        break;
      }
      dest[i] = src[i];
    }

    return dest;
  } else {
    return std::strncpy(dest, src, count);
  }
#endif
}

constexpr char* strcpy(char* dest, const char* src) noexcept {
  return strncpy(dest, src, strlen(src));
}

constexpr char* strncat(char* dest, const char* src, std::size_t count) noexcept {
  strncpy(dest + strlen(dest), src, count);

  return dest;
}

constexpr char* strcat(char* dest, const char* src) noexcept {
  return strncat(dest, src, strlen(src));
}

// constexpr work with a locale requires constexpr locale.
std::size_t strxfrm(char* dest, const char* src, std::size_t count) noexcept {
  return std::strxfrm(dest, src, count);
}

constexpr int strcmp(const char* lhs, const char* rhs) noexcept {
  const std::size_t lhs_len = strlen(lhs);
  const std::size_t rhs_len = strlen(rhs);
  const std::size_t len = std::min(lhs_len, rhs_len);
#if defined(__clang__) || defined(_MSC_VER)
  if (const int ans = __builtin_memcmp(lhs, rhs, len); ans != 0) {
    return ans;
  }

  if (lhs_len != rhs_len) {
    return lhs_len < rhs_len ? -1 : 1;
  }

  return 0;
#elif defined(__GNUC__)
// gcc-9 error: __builtin_memcmp is not a constant expression!
  if (std::is_constant_evaluated()) {
    for (std::size_t i = 0; i < len; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      }
    }

    if (lhs_len != rhs_len) {
      return lhs_len < rhs_len ? -1 : 1;
    }

    return 0;
  } else {
    return std::strcmp(lhs, rhs);
  }
#endif
}

constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept {
#if defined(__clang__) || defined(_MSC_VER)
  return __builtin_memcmp(lhs, rhs, count);
#elif defined(__GNUC__)
// gcc-9 error: __builtin_memcmp is not a constant expression!
  if (std::is_constant_evaluated()) {
    for (std::size_t i = 0; i < count; ++i) {
      if (lhs[i] != rhs[i]) {
        return lhs[i] < rhs[i] ? -1 : 1;
      }
    }

    return 0;
  } else {
    return std::strncmp(lhs, rhs, count);
  }
#endif
}

// constexpr work with a locale requires constexpr locale.
int strcoll(const char* lhs, const char* rhs) noexcept {
  return std::strcoll(lhs, rhs);
}

constexpr int memcmp(const void* lhs, const void* rhs, std::size_t count) noexcept {
#if defined(__clang__) || defined(_MSC_VER)
  return __builtin_memcmp(lhs, rhs, count);
#endif
}

} // namespace proposal
