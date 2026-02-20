
## Overview

This repository holds multiple C++ projects written during university. Each project is contained in its own folder with source code, a `README` describing how to build and run, and example input where applicable.

Included projects:

* `bank-management/` — console-based bank system: accounts, transactions, file persistence (serialization).
* `phonebook-cli/` — command-line phonebook utility with search, add, delete, and save/load.
* `phonebook-qt/` — GUI phonebook built with Qt (Qt5/Qt6 compatible notes included).
* `samples/` — smaller exercises and assignments (sorting, data structures, algorithms).

---

## Build & run

General recommendations for building (per-project `README` files provide specifics):

Using `g++` (example):

```bash
cd bank-management
mkdir build && cd build
cmake ..   # if CMakeLists.txt is present
make
./bank-management
```

Or simple compile:

```bash
g++ -std=c++17 src/*.cpp -o bank-management
./bank-management
```

Qt project:

```bash
cd phonebook-qt
qmake && make   # or use CMake if provided
./phonebook-qt
```

---

## What should notice

* Clear separation between CLI and GUI implementations.
* Use of modern C++ features where applicable (RAII, smart pointers, STL containers).
* Basic file I/O and simple persistence in several projects.
* Documentation in each project folder explaining design decisions and limitations.
