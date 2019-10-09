
#pragma once

namespace nstd {

namespace detail {

// Temporary, until there is no full support.
#if defined(__GNUC__) || defined(__clang__)
inline constexpr bool is_constant_evaluated() noexcept {
  return __builtin_is_constant_evaluated();
}
#elif defined(_MSC_VER)
inline constexpr bool is_constant_evaluated() noexcept {
  return true;
}
#endif

} // namespace nstd::detail

} // namespace nstd
