# Add Constexpr Modifiers to Functions in `<cstring>` and `<cwchar>` Headers

Daniil Goncharov <neargye@gmail.com>

Antony Polukhin <antoshkka@gmail.com>

# I. Introduction and Motivation

Headers `<cstring>` and `<cwchar>` has is widely-used functions for string manipulation and in C++20 these functions not currently constexpr friendly.

Consider the simple example:
```cpp
int main() {
    constexpr char[] str = "abcd"; // OK
    constexpr auto str_len = std::strlen(str); // Fail
}
```

# II. Impact on the Standard
This proposal is a pure library extension. It proposes changes to existing headers `<cstring>` and `<cwchar>` such that the changes do not break existing code and do not degrade performance. It does not require any changes in the core language in simple cases of non assembly optimized Standard Library, and it could be implemented in standard C++, except for the memchr, memcmp, memset, memcpy and memmove functions.

# III. Design Decisions

## A. `<cstring>` must have constexpr additions

All the functions from `<cstring>` header must be marked with constexpr, except the `strcoll`, `strxfrm`, `strtok`, `strerror` functions.

For example constexpr `std::strlen` helps make code constexpr friendly without breaking backward compatibility.
```cpp
    constexpr char[] str = "abcd";
    constexpr auto str_len = std::strlen(str);
    std::array<char, str_len> str_array;
```

`strcoll`, `strxfrm` locale non constexpr context.
`strtok` each call to this function modifies a static variable, so can't be constexpr.
`strerror` system error code non constexpr context.

## B. std::memchr, std::memcmp, std::memchr, std::memset, std::memcpy, std::memmove must have constexpr additions

`std::memchr`, `std::memcmp`, `std::memchr`, `std::memset`, `std::memcpy`, `std::memmove` accept `void*` and `const void*` parameters. This makes them impossible to implement in pure C++ as constexpr, because constant expressions can not evaluate a conversion from type cv `void *` to a pointer-to-object type according to [expr.const].

However those functions are not only popular, but also are widely used across Standard Library to gain better performance. Not making them constexpr will force standard Library developer to have compiler intrinsics for them anyway. This is a hard step that must be done.

Clang already support constexpr __builtin_memchr, __builtin_memcmp, __builtin_memcpy, __builtin_memmove <https://reviews.llvm.org/rL338941>.

## C. Add strtok(char* str, const char* delim, char** ptr)

Unlike `strtok(char* str, const char* delim)`, this function does not update static storage: it stores the parser state in the user-provided location, so it's can be using in constexpr.

```cpp
constexpr char* strtok(char* str, const char* delim, char** ptr);
```

## D. Functions string manipulation, string examination and wide character array manipulation from `<cwchar>` must have constexpr additions

Multibyte string manipulation functions must have constexpr additions:
`wcscpym`, `wcsncpy`, `wcscat`, `wcsncat` functions must be marked with constexpr.

Multibyte string examination functions must have constexpr additions:
`wcslen`, `wcscmp`, `wcsncmp,` `wcschr`, `wcsrchr`, `wcsspn`, `wcscspn`, `wcspbrk`, `wcsstr`, `wcstok` functions must be marked with constexpr.

Wide character array manipulation functions must have constexpr additions: `wmemcpy`, `wmemmove`, `wmemcmp`, `wmemchr`, `wmemset` functions must be marked with constexpr.

As well as similar functions from `<cstrings>` for char, these functions from `<cwchar>` useful when working with wchar_t in constexpr.

# IV. Proposed wording

All the additions to the Standard are marked with <font color='green'>underlined green</font>.

## A. Modifications to "21.8 Null-terminated sequence utilities" [c.strings]

<font color='green'>constexpr</font> char* strcpy(char* dest, const char* src);

<font color='green'>constexpr</font> char* strncpy(char* dest, const char* src, std::size_t count);

<font color='green'>constexpr</font> char* strcat(char* dest, const char* src);

<font color='green'>constexpr</font> char* strncat(char* dest, const char* src, std::size_t count);

<font color='green'>constexpr</font> std::size_t strlen(const char* str);

<font color='green'>constexpr</font> int strcmp(const char* lhs, const char* rhs);

<font color='green'>constexpr</font> int strncmp(const char* lhs, const char* rhs, std::size_t count);

<font color='green'>constexpr</font> const char* strchr(const char* str, int ch);

<font color='green'>constexpr</font> char* strchr(char* str, int ch);

<font color='green'>constexpr</font> const char* strrchr(const char* str, int ch);

<font color='green'>constexpr</font> char* strrchr(char* str, int ch);

<font color='green'>constexpr</font> std::size_t strspn(const char* dest, const char* src);

<font color='green'>constexpr</font> std::size_t strcspn(const char* dest, const char* src);

<font color='green'>constexpr</font> const char* strpbrk(const char* dest, const char* breakset);

<font color='green'>constexpr</font> char* strpbrk(char* dest, const char* breakset);

<font color='green'>constexpr</font> const char* strstr(const char* str, const char* target);

<font color='green'>constexpr</font> char* strstr(char* str, const char* target);

<font color='green'>constexpr char* strtok(char* str, const char* delim, char** ptr);</font>

<font color='green'>constexpr</font> const void* memchr(const void* ptr, int ch, std::size_t count);

<font color='green'>constexpr</font> void* memchr(void* ptr, int ch, std::size_t count);

<font color='green'>constexpr</font> int memcmp(const void* lhs, const void* rhs, std::size_t count);

<font color='green'>constexpr</font> void* memset(void* dest, int ch, std::size_t count);

<font color='green'>constexpr</font> void* memcpy(void* dest, const void* src, std::size_t count);

<font color='green'>constexpr</font> void* memmove(void* dest, const void* src, std::size_t count);

## B. Modifications to "21.8 Null-terminated sequence utilities" [c.wchar]

<font color='green'>constexpr</font> wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);

<font color='green'>constexpr</font> wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, std::size_t count);

<font color='green'>constexpr</font> wchar_t* wcscat(wchar_t* dest, const wchar_t* src);

<font color='green'>constexpr</font> wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, std::size_t count);

<font color='green'>constexpr</font> std::size_t wcslen(const wchar_t* str);

<font color='green'>constexpr</font> int wcscmp(const wchar_t* lhs, const wchar_t* rhs);

<font color='green'>constexpr</font> int wcsncmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count);

<font color='green'>constexpr</font> const wchar_t* wcschr(const wchar_t* str, wchar_t ch);

<font color='green'>constexpr</font> wchar_t* wcschr(wchar_t* str, wchar_t ch);

<font color='green'>constexpr</font> const wchar_t* wcsrchr(const wchar_t* str, wchar_t ch);

<font color='green'>constexpr</font> wchar_t* wcsrchr(wchar_t* str, wchar_t ch);

<font color='green'>constexpr</font> std::size_t wcsspn(const wchar_t* dest, const wchar_t* src);

<font color='green'>constexpr</font> std::size_t wcscspn(const wchar_t* dest, const wchar_t* src);

<font color='green'>constexpr</font> const wchar_t* wcspbrk(const wchar_t* dest, const wchar_t* breakset);

<font color='green'>constexpr</font> wchar_t* wcspbrk(wchar_t* dest, const wchar_t* breakset);

<font color='green'>constexpr</font> const wchar_t* wcsstr(const wchar_t* str, const wchar_t* target);

<font color='green'>constexpr</font> wchar_t* wcsstr(wchar_t* str, const wchar_t* target);

<font color='green'>constexpr</font> wchar_t* wcstok(wchar_t* str, const wchar_t* delim, wchar_t** ptr);

<font color='green'>constexpr</font> wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, std::size_t count);

<font color='green'>constexpr</font> wchar_t* wmemmove(wchar_t* dest, const wchar_t* src, std::size_t count);

<font color='green'>constexpr</font> int wmemcmp(const wchar_t* lhs, const wchar_t* rhs, std::size_t count);

<font color='green'>constexpr</font> const wchar_t* wmemchr(const wchar_t* ptr, wchar_t ch, std::size_t count);

<font color='green'>constexpr</font> wchar_t* wmemchr(wchar_t* ptr, wchar_t ch, std::size_t count);

<font color='green'>constexpr</font> wchar_t* wmemset(wchar_t* dest, wchar_t ch, std::size_t count);

# V. Revision History

Revision 0:
* Initial proposal

# VI. References:
* [neargye] Proof of concept for `<cstrings>` and `<cwchar>` functions <https://github.com/Neargye/cstring-constexpr-proposal>.
* [P0202R0] A Proposal to Add Constexpr Modifiers to Functions in <algorithm> and <cstring> Headers <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0202r0.html>.