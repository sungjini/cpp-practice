# hello-world

[![Build Status](https://travis-ci.com/sungjini/cpp-practice.svg?branch=master)](https://travis-ci.com/sungjini/cpp-practice)

# environmenet

support for development

github


# Reference Document 

## c++ compiler support

* https://en.cppreference.com/w/cpp/compiler_support
* https://gcc.gnu.org/projects/cxx-status.html


# Tools

### travis

github, travis 연동
* https://lindarex.github.io/travis-ci/travis-github-pages-jekyll-setting/

travis 설정
* https://docs.travis-ci.com/user/languages/cpp/
* http://david-grs.github.io/cpp-clang-travis-cmake-gtest-coveralls-appveyor/

### coveralls

* https://coveralls.io/github/sungjini/cpp-practice


### sanitizer

(base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice$ ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-3.8 clang++ sanitizer_test.cpp -fsanitize=address -g
sanitizer_test.cpp:6:25: warning: array index 3 is past the end of the array (which contains 2 elements) [-Warray-bounds]
 std::string last_arg = names[3];
                         ^     ~
												 sanitizer_test.cpp:5:2: note: array 'names' declared here
												  const char *names[] = {"bob", "fred"};
 ^
 1 warning generated.

 (base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice$ ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-3.8 ./a.out
 =================================================================
 ==8726==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7fff698d0138 at pc 0x0000004ed36d bp 0x7fff698d00f0 sp 0x7fff698d00e8
 READ of size 8 at 0x7fff698d0138 thread T0
 ==8726==ERROR: External symbolizer path is set to '/usr/bin/llvm-symbolizer-3.8' which isn't a known symbolizer. Please set the path to the llvm-symbolizer binary or other known tool.

 (base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice$ ASAN_SYMBOLIZER_PATH=/usr/lib/llvm-3.8/bin/llvm-symbolizer ./a.out
 =================================================================
 ==8729==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffd81150038 at pc 0x0000004ed36d bp 0x7ffd8114fff0 sp 0x7ffd8114ffe8
 READ of size 8 at 0x7ffd81150038 thread T0
     #0 0x4ed36c in main /home/sjcho/Cpp/cpp-practice/sanitizer_test.cpp:6:25
     #1 0x7f11c96fd82f in __libc_start_main /build/glibc-LK5gWL/glibc-2.23/csu/../csu/libc-start.c:291
     #2 0x418da8 in _start (/home/sjcho/Cpp/cpp-practice/a.out+0x418da8)

 Address 0x7ffd81150038 is located in stack of thread T0 at offset 56 in frame
     #0 0x4ed22f in main /home/sjcho/Cpp/cpp-practice/sanitizer_test.cpp:4

   This frame has 3 object(s):
		    [32, 48) 'names'
				     [64, 96) 'last_arg' <== Memory access at offset 56 underflows this variable
					     [128, 129) ''
						HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
						       (longjmp and C++ exceptions *are* supported)
						 SUMMARY: AddressSanitizer: stack-buffer-overflow /home/sjcho/Cpp/cpp-practice/sanitizer_test.cpp:6:25 in main
											Shadow bytes around the buggy address:
													   0x100030221fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
														   0x100030221fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															  0x100030221fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030221fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030221ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															 =>0x100030222000: f1 f1 f1 f1 00 00 f2[f2]00 00 00 00 f2 f2 f2 f2
															   0x100030222010: 01 f3 f3 f3 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030222020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030222030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030222040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															   0x100030222050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
															 Shadow byte legend (one shadow byte represents 8 application bytes):
																  Addressable:           00
																	  Partially addressable: 01 02 03 04 05 06 07
																	   Heap left redzone:       fa
																	   Heap right redzone:      fb
																	   Freed heap region:       fd
																	   Stack left redzone:      f1
																	   Stack mid redzone:       f2
																	   Stack right redzone:     f3
																	   Stack partial redzone:   f4
																	   Stack after return:      f5
																	   Stack use after scope:   f8
																	   Global redzone:          f9
																	   Global init order:       f6
																	   Poisoned by user:        f7
																	   Container overflow:      fc
																	   Array cookie:            ac
																	   Intra object redzone:    bb
																	   ASan internal:           fe
																	   Left alloca redzone:     ca
																	   Right alloca redzone:    cb
																	 ==8729==ABORTING
																	 (base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice$

#### memory sanitizer

(base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice/tools$ clang++ memory.cpp -Wall -Wextra -fsanitize=memory
(base) sjcho@ubuntu-home-dev:~/Cpp/cpp-practice/tools$ ./a.out
==8990==WARNING: MemorySanitizer: use-of-uninitialized-value
    #0 0x4892bb  (/home/sjcho/Cpp/cpp-practice/tools/a.out+0x4892bb)
    #1 0x7f86a9c0f82f  (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #2 0x419ad8  (/home/sjcho/Cpp/cpp-practice/tools/a.out+0x419ad8)

SUMMARY: MemorySanitizer: use-of-uninitialized-value (/home/sjcho/Cpp/cpp-practice/tools/a.out+0x4892bb)
Exiting

### fuzzy test

### valgrind

callgrind
kcachegrind
