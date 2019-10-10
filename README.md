# Add Constexpr Modifiers to Functions in `<cstring>` and `<cwchar>` Headers

Antony Polukhin <antoshkka@gmail.com>

Daniil Goncharov <neargye@gmail.com>

# Impact on the Standard
This proposal is a pure library extension. It proposes changes to existing headers `<cstring>` and `<cwchar>` such that the changes do not break existing code and do not degrade performance. It does not require any changes in the core language in simple cases of non assembly optimized Standard Library, and it could be implemented in standard C++, except for the memcpy and memmove functions.

# Design Decisions

## A. `<cstring>` must have constexpr additions

All the functions from `<cstring>` header must be marked with constexpr, except the strcoll, strxfrm, strtok, strerror functions.

## B. std::memchr, std::memcmp, std::memchr, std::memset, std::memcpy, std::memmove must have constexpr additions

`std::memchr`, `std::memcmp`, `std::memchr`, `std::memset`, `std::memcpy`, `std::memmove` accept `void*` and `const void*` parameters. This makes them impossible to implement in pure C++ as constexpr, because constant expressions can not evaluate a conversion from type cv `void *` to a pointer-to-object type according to [expr.const].

However those functions are not only popular, but also are widely used across Standard Library to gain better performance. Not making them constexpr will force standard Library developer to have compiler intrinsics for them anyway. This is a hard step that must be done.

Clang already support constexpr __builtin_memchr, __builtin_memcmp, __builtin_memset, __builtin_memcpy, __builtin_memmove:
* https://github.com/llvm-mirror/clang/blob/master/test/SemaCXX/constexpr-string.cpp
* https://rev.ng/gitlab/revng-bar-2019/clang/commit/0f097ac04fc21e27a382b6b896f52a12e0c02b97

# C. Add strtok(char* str, const char* delim, char** ptr)

Unlike std::strtok, this function does not update static storage: it stores the parser state in the user-provided location.
```cpp
constexpr char* strtok(char* str, const char* delim, char** ptr);
```

# D. `<cwchar>` must have constexpr additions

wcscpym, wcsncpy, wcscat, wcsncat, wcslen, wcscmp, wcsncmp, wcschr, wcsrchr, wcsspn, wcscspn, wcspbrk, wcsstr, wcstok, wmemcpy, wmemmove, wmemcmp, wmemchr, wmemset functions from `<cwchar>` header must be marked with constexpr.

# Modifications to "21.8 Null-terminated sequence utilities" [c.strings]

```cpp
namespace std {

constexpr char* strcpy(char* dest, const char* src);
constexpr char* strncpy(char* dest, const char* src, std::size_t count);
constexpr char* strcat(char* dest, const char* src);
constexpr char* strncat(char* dest, const char* src, std::size_t count);

std::size_t strxfrm(char* dest, const char* src, std::size_t count);

constexpr std::size_t strlen(const char* str);
constexpr int strcmp(const char* lhs, const char* rhs);
constexpr int strncmp(const char* lhs, const char* rhs, std::size_t count);

int strcoll(const char* lhs, const char* rhs);

constexpr const char* strchr(const char* str, int ch);
constexpr char* strchr(char* str, int ch);
constexpr const char* strrchr(const char* str, int ch);
constexpr char* strrchr(char* str, int ch);
constexpr std::size_t strspn(const char* dest, const char* src);
constexpr std::size_t strcspn(const char* dest, const char* src);
constexpr const char* strpbrk(const char* dest, const char* breakset);
constexpr char* strpbrk(char* dest, const char* breakset);
constexpr const char* strstr(const char* str, const char* target);
constexpr char* strstr(char* str, const char* target);

char* strtok(char* str, const char* delim);
constexpr char* strtok(char* str, const char* delim, char** ptr);

constexpr const void* memchr(const void* ptr, int ch, std::size_t count);
constexpr void* memchr(void* ptr, int ch, std::size_t count);
constexpr int memcmp(const void* lhs, const void* rhs, std::size_t count);
constexpr void* memset(void* dest, int ch, std::size_t count);
constexpr void* memcpy(void* dest, const void* src, std::size_t count);
constexpr void* memmove(void* dest, const void* src, std::size_t count);

char* strerror(int errnum);

} // namespace std
```

# Modifications to "21.8 Null-terminated sequence utilities" [c.wchar]

```cpp
namespace std {

constexpr wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);
constexpr wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, std::size_t count);
constexpr wchar_t* wcscat(wchar_t* dest, const wchar_t* src);
constexpr wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, std::size_t count);

std::size_t wcsxfrm(wchar_t* dest, const wchar_t* src, std::size_t count);

constexpr std::size_t wcslen(const wchar_t* str);
constexpr int wcscmp(const wchar_t* lhs, const wchar_t* rhs);
constexpr int wcsncmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count);

int wcscoll(const wchar_t* lhs, const wchar_t* rhs);

constexpr const wchar_t* wcschr(const wchar_t* str, wchar_t ch);
constexpr wchar_t* wcschr(wchar_t* str, wchar_t ch);
constexpr const wchar_t* wcsrchr(const wchar_t* str, wchar_t ch);
constexpr wchar_t* wcsrchr(wchar_t* str, wchar_t ch);
constexpr std::size_t wcsspn(const wchar_t* dest, const wchar_t* src);
constexpr std::size_t wcscspn(const wchar_t* dest, const wchar_t* src);
constexpr const wchar_t* wcspbrk(const wchar_t* dest, const wchar_t* breakset);
constexpr wchar_t* wcspbrk(wchar_t* dest, const wchar_t* breakset);
constexpr const wchar_t* wcsstr(const wchar_t* str, const wchar_t* target);
constexpr wchar_t* wcsstr(wchar_t* str, const wchar_t* target);

constexpr wchar_t* wcstok(wchar_t* str, const wchar_t* delim, wchar_t** ptr);

constexpr wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, std::size_t count);
constexpr wchar_t* wmemmove(wchar_t* dest, const wchar_t* src, std::size_t count);
constexpr int wmemcmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count);
constexpr const wchar_t* wmemchr(const wchar_t* ptr, wchar_t ch, std::size_t count);
constexpr wchar_t* wmemchr(wchar_t* ptr, wchar_t ch, std::size_t count);
constexpr wchar_t* wmemset(wchar_t* dest, wchar_t ch, std::size_t count);

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
