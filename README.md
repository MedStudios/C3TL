# C3TL

[![Build Status](https://travis-ci.org/MedStudios/C3TL.svg?branch=master)](https://travis-ci.org/MedStudios/C3TL) ![Travis (.org) branch](https://img.shields.io/travis/MedStudios/C3TL/dev?label=dev-build) ![GitHub](https://img.shields.io/github/license/MedStudios/C3TL)

C3TL | 一个 C++11 STL 的不完全实现

~~这是我们高级语言程序设计课程的大作业，ddl 越收越紧，在这种情况下，~~ C3TL 注定无法全部实现，且已实现的部分也不是很规范，有些算法的复杂度比 STL 差远了。珍惜生命，慎用本库 〒▽〒

这个库是出于学习理解 C++ STL 运行原理与锻炼编码技能的目的开发的，加之重复造轮子 + 完成度太烂，这个库我们**将来不会主动维护**；但是如果有 Issue 和 Pull Request 我们仍然会积极采纳，也欢迎各位提出 Issue 和 Pull Request。

## 构建 / 运行测试

### 编译器版本

需要支持 C++11 的编译器方可成功编译：
 - GCC 4.8.1 及以上
 - Clang 3.3 及以上
 - MSVC++ 14.0 (Visual Studio 2015) 及以上

### 脚本

```bash
$ mkdir build && cd build
$ cmake ..
$ make
$ ./C3TL
```
