# Add Constexpr Modifiers to Functions in <cstring> Headers

Antony Polukhin <antoshkka@gmail.com>

Daniil Goncharov <neargye@gmail.com>

# Impact on the Standard
This proposal is a pure library extension. It proposes changes to existing headers `<cstring>` such that the changes do not break existing code and do not degrade performance. It does not require any changes in the core language in simple cases of non assembly optimized Standard Library, and it could be implemented in standard C++, except for the memcpy and memmove functions.

# Design Decisions

## A. <cstring> must have constexpr additions

All the functions from `<cstring>` header must be marked with constexpr, except the strcoll, strxfrm, strtok, strerror functions.

## B. std::memmove and std::memcpy must have constexpr additions

`std::memmove` and `std::memcpy` accept `void*` and `const void*` parameters. This makes them impossible to implement in pure C++ as constexpr, because constant expressions can not evaluate a conversion from type cv `void *` to a pointer-to-object type according to [expr.const].

However those functions are not only popular, but also are widely used across Standard Library to gain better performance. Not making them constexpr will force standard Library developer to have compiler intrinsics for them anyway. This is a hard step that must be done.

Clang already support constexpr __builtin_memchr, __builtin_memcmp, __builtin_memset, __builtin_memcpy, __builtin_memmove:
* https://github.com/llvm-mirror/clang/blob/master/test/SemaCXX/constexpr-string.cpp
* https://rev.ng/gitlab/revng-bar-2019/clang/commit/0f097ac04fc21e27a382b6b896f52a12e0c02b97

# Modifications to "21.8 Null-terminated sequence utilities" [c.strings]

```cpp
namespace std {

constexpr char* strcpy(char* dest, const char* src) noexcept; // gcc, clang, msvc
constexpr char* strncpy(char* dest, const char* src, std::size_t count) noexcept; // gcc, clang, msvc
constexpr char* strcat(char* dest, const char* src) noexcept; // gcc, clang, msvc
constexpr char* strncat(char* dest, const char* src, std::size_t count) noexcept; // gcc, clang, msvc

std::size_t strxfrm(char* dest, const char* src, std::size_t count) noexcept; // gcc, clang, msvc

constexpr std::size_t strlen(const char* str) noexcept; // gcc, clang, msvc
constexpr int strcmp(const char* lhs, const char* rhs) noexcept; // gcc, clang, msvc
constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept; // gcc, clang, msvc

int strcoll(const char* lhs, const char* rhs) noexcept; // gcc, clang, msvc

constexpr const char* strchr(const char* str, int ch) noexcept; // gcc, clang, msvc
constexpr char* strchr(char* str, int ch) noexcept; // gcc, clang, msvc
constexpr const char* strrchr(const char* str, int ch) noexcept; // gcc, clang, msvc
constexpr char* strrchr(char* str, int ch) noexcept; // gcc, clang, msvc
constexpr std::size_t strspn(const char* dest, const char* src) noexcept; // gcc, clang, msvc
constexpr std::size_t strcspn(const char* dest, const char* src) noexcept; // gcc, clang, msvc
constexpr const char* strpbrk(const char* dest, const char* breakset) noexcept; // gcc, clang, msvc
constexpr char* strpbrk(char* dest, const char* breakset) noexcept; // gcc, clang, msvc
constexpr const char* strstr(const char* str, const char* target) noexcept; // gcc, clang, msvc
constexpr char* strstr(char* str, const char* target) noexcept; // gcc, clang, msvc

char* strtok(char* str, const char* delim) noexcept; // gcc, clang, msvc

constexpr const void* memchr(const void* ptr, int ch, std::size_t count) noexcept; // clang
constexpr void* memchr(void* ptr, int ch, std::size_t count) noexcept; // clang
constexpr int memcmp(const void* lhs, const void* rhs, std::size_t count) noexcept; // clang, msvc
constexpr void* memset(void* dest, int ch, std::size_t count) noexcept; // 0
constexpr void* memcpy(void* dest, const void* src, std::size_t count) noexcept; // clang
constexpr void* memmove(void* dest, const void* src, std::size_t count) noexcept; // clang

char* strerror(int errnum) noexcept;

} // namespace std
```

# References:
* https://stdcpp.ru/proposals/b6000ec7-9db8-41b1-9a1e-1fe00a424bbd
* http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0202r0.html
* https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/include/bits/char_traits.h
* https://github.com/freebsd/freebsd/tree/master/sys/libkern

# Tested:
[![Build Status](https://travis-ci.org/Neargye/cstring-constexpr-proposal.svg?branch=master)](https://travis-ci.org/Neargye/cstring-constexpr-proposal)
[![Build status](https://ci.appveyor.com/api/projects/status/af05o6972g9bc4ec/branch/master?svg=true)](https://ci.appveyor.com/project/Neargye/cstring-constexpr-proposal/branch/master)

* GCC 9
* Clang 9
* MSVC 1923 (Visual Studio 16.3.2)
