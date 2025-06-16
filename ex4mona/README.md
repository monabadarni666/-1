
# MyContainer Project

**email:** 

## Overview

This project provides a generic C++ container (**`ac::MyContainer`**) that stores *comparable* objects
and exposes six custom iterator types:

| Iterator                | Behaviour                                               |
|-------------------------|---------------------------------------------------------|
| **AscendingOrder**      | Smallest → largest                                      |
| **DescendingOrder**     | Largest → smallest                                      |
| **SideCrossOrder**      | Alternates smallest / largest, continuing inward       |
| **Order**               | Insertion order (default `begin()` / `end()`)           |
| **ReverseOrder**        | Reverse insertion order (`rbegin()` / `rend()`)         |
| **MiddleOutOrder**      | Starts at the middle index, alternates right / left     |

All functionality is header‑only (`include/ac/MyContainer.hpp`).

## File Structure

```
.
├── include
│   └── ac
│       └── MyContainer.hpp   # container & iterator implementation
├── main.cpp                  # demonstration program (target: `make Main`)
├── tests.cpp                 # unit tests with doctest (target: `make test`)
├── Makefile                  # build / test / valgrind targets
└── README.md                 # this file
```

## Building

```bash
# build and run demo
make Main    # produces ./main
./main

# run unit tests
make test

# memory‑leak analysis (requires valgrind)
make valgrind
```

Ensure `doctest.h` is accessible via your include path (either system‑wide or placed in the project root).

## Notes

* The container operations throw `std::runtime_error` when attempting to remove a value that does not exist.
* All iterators are **forward iterators** and remain valid as long as the container is not modified.
* The implementation passes `-Wall -Wextra -pedantic` and is leak‑free under `valgrind` (tested on g++‑13 / C++20).
