# Add Constexpr Modifiers to Functions in `<cstring>` and `<cwchar>` Headers

Daniil Goncharov <neargye@gmail.com>

Antony Polukhin <antoshkka@gmail.com>

# Full Text for Proposal

* [P1944R0](papers/P1944R0.pdf)

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
