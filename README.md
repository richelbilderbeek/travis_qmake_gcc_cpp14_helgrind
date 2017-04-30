# travis_qmake_gcc_cpp14_helgrind

Branch|[![Travis CI logo](TravisCI.png)](https://travis-ci.org)
---|---
master|[![Build Status](https://travis-ci.org/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind.svg?branch=master)](https://travis-ci.org/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind)
develop|[![Build Status](https://travis-ci.org/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind.svg?branch=develop)](https://travis-ci.org/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind)

This GitHub is part of [the Travis C++ Tutorial](https://github.com/richelbilderbeek/travis_cpp_tutorial).

The goal of this project is to have a clean Travis CI build, with specs:

 * Build system: `qmake`
 * C++ compiler: `gcc`
 * C++ version: `C++14`
 * Libraries: `STL` only
 * Code coverage: none
 * Added tools: `helgrind`
 * Source: one single file, `main.cpp`

More complex builds:

 * [none]

Less complex builds:

 * C++98: [travis_qmake_gcc_cpp98_helgrind](https://www.github.com/richelbilderbeek/travis_qmake_gcc_cpp98_helgrind) (should fail)
 * C++11: [travis_qmake_gcc_cpp11_helgrind](https://www.github.com/richelbilderbeek/travis_qmake_gcc_cpp11_helgrind)
 * No `helgrind`: [travis_qmake_gcc_cpp14](https://www.github.com/richelbilderbeek/travis_qmake_gcc_cpp14) 

## Results

`helgrind` correctly detects the data race in `DoCountDown`:

```
==5104== 3 errors in context 5 of 5:
==5104== ----------------------------------------------------------------
==5104== 
==5104== Possible data race during write of size 8 at 0x602138 by thread #2
==5104== Locks held: none
==5104==    at 0x62A94F5: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22)
==5104==    by 0x401046: DoCountDown(int) (in /home/travis/build/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind/travis_qmake_gcc_cpp14_helgrind)
==5104==    by 0x6283C2F: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22)
==5104==    by 0x4C30FA6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5104==    by 0x5FDD183: start_thread (pthread_create.c:312)
==5104==    by 0x6B1FBEC: clone (clone.S:111)
==5104== 
==5104== This conflicts with a previous read of size 8 by thread #3
==5104== Locks held: none
==5104==    at 0x62A943F: std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22)
==5104==    by 0x401003: DoCountDown(int) (in /home/travis/build/richelbilderbeek/travis_qmake_gcc_cpp14_helgrind/travis_qmake_gcc_cpp14_helgrind)
==5104==    by 0x6283C2F: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.22)
==5104==    by 0x4C30FA6: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5104==    by 0x5FDD183: start_thread (pthread_create.c:312)
==5104==    by 0x6B1FBEC: clone (clone.S:111)
==5104==  Address 0x602138 is 24 bytes inside data symbol "_ZSt4cout@@GLIBCXX_3.4"
==5104== 
--5104-- 
--5104-- used_suppression:     46 helgrind-glibc2X-004 /usr/lib/valgrind/default.supp:927
--5104-- used_suppression:      1 helgrind-glibc2X-101 /usr/lib/valgrind/default.supp:968
==5104== 
==5104== ERROR SUMMARY: 9 errors from 5 contexts (suppressed: 47 from 26)
```