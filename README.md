# cstring constexpr proposals

[![Build Status](https://travis-ci.org/Neargye/cstring-constexpr-proposal.svg?branch=master)](https://travis-ci.org/Neargye/cstring-constexpr-proposal)
[![Build status](https://ci.appveyor.com/api/projects/status/af05o6972g9bc4ec/branch/master?svg=true)](https://ci.appveyor.com/project/Neargye/cstring-constexpr-proposal/branch/master)

All the functions from <cstring> header must be marked with constexpr, except the strcoll, strxfrm, strtok, strerror functions.

```cpp
constexpr char* strcpy(char* dest, const char* src) noexcept;
constexpr char* strncpy(char* dest, const char* src, std::size_t count) noexcept;
constexpr char* strcat(char* dest, const char* src) noexcept;
constexpr char* strncat(char* dest, const char* src, std::size_t count) noexcept;

std::size_t strxfrm(char* dest, const char* src, std::size_t count) noexcept;

constexpr std::size_t strlen(const char* str) noexcept;
constexpr int strcmp(const char* lhs, const char* rhs) noexcept;
constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept;

int strcoll(const char* lhs, const char* rhs) noexcept;

constexpr const char* strchr(const char* str, int ch) noexcept;
constexpr char* strchr(char* str, int ch) noexcept;
constexpr const char* strrchr(const char* str, int ch) noexcept;
constexpr char* strrchr(char* str, int ch) noexcept;
constexpr std::size_t strspn(const char* dest, const char* src) noexcept;
constexpr std::size_t strcspn(const char* dest, const char* src) noexcept;
constexpr const char* strpbrk(const char* dest, const char* breakset) noexcept;
constexpr char* strpbrk(char* dest, const char* breakset) noexcept;
constexpr const char* strstr(const char* str, const char* target) noexcept;
constexpr char* strstr(char* str, const char* target) noexcept;

char* strtok(char* str, const char* delim) noexcept;

constexpr int memcmp(const void* lhs, const void* rhs, std::size_t count) noexcept;

char* strerror(int errnum) noexcept;
```

# References:
* https://stdcpp.ru/proposals/b6000ec7-9db8-41b1-9a1e-1fe00a424bbd
* http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0202r0.html
* https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/include/bits/char_traits.h
* https://github.com/freebsd/freebsd/tree/master/sys/libkern

# Tested:
* GCC 9
* Clang 9
* MSVC 1923 (Visual Studio 16.3.2)
