
#pragma once

namespace nstd {

namespace detail {

// Temporary, until there is no full support.
inline constexpr bool is_constant_evaluated() noexcept {
#if defined(__GNUC__) || defined(__clang__)
  return __builtin_is_constant_evaluated();
#elif defined(_MSC_VER)
  return true;
#endif
}

} // namespace nstd::detail

} // namespace nstd
