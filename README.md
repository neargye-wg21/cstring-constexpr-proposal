# constexpr <cstring> proposals

[![Build Status](https://travis-ci.org/Neargye/cstring-constexpr-proposal.svg?branch=master)](https://travis-ci.org/Neargye/cstring-constexpr-proposal)
[![Build status](https://ci.appveyor.com/api/projects/status/af05o6972g9bc4ec/branch/master?svg=true)](https://ci.appveyor.com/project/Neargye/cstring-constexpr-proposal/branch/master)

See https://stdcpp.ru/proposals/b6000ec7-9db8-41b1-9a1e-1fe00a424bbd.

```cpp
constexpr char* strcpy(char* dest, const char* src) noexcept;
constexpr char* strncpy(char* dest, const char* src, std::size_t count) noexcept;
constexpr char* strcat(char* dest, const char* src) noexcept;
constexpr char* strncat(char* dest, const char* src, std::size_t count) noexcept;

constexpr std::size_t strlen(const char* str) noexcept;
constexpr int strcmp(const char* lhs, const char* rhs) noexcept;
constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count) noexcept;
```

Tested:
* GCC 9
* MSVC 1923 (Visual Studio 16.3.2)
