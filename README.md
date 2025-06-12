# libasm

A 64-bit assembly library (`libasm.a`) reimplementing several standard C library functions and basic linked list operations. This project is designed to deepen your understanding of low-level programming, system calls, and memory management in assembly.

---

## Features

### Mandatory Functions (in `libasm/`)
- **ft_strlen**: Computes the length of a string.
- **ft_strcpy**: Copies a string.
- **ft_strcmp**: Compares two strings.
- **ft_write**: Writes data to a file descriptor (with proper `errno` handling).
- **ft_read**: Reads data from a file descriptor (with proper `errno` handling).
- **ft_strdup**: Duplicates a string.

### Bonus Functions (in `libasm/`)
- **ft_atoi_base**: Converts a string to an integer using a given base.
- **ft_list_push_front**: Adds an element to the front of a linked list.
- **ft_list_size**: Returns the size of a linked list.
- **ft_list_sort**: Sorts a linked list.
- **ft_list_remove_if**: Removes elements from a linked list matching a condition.

---

## Project Structure

```
libasm/
├── Makefile
├── README.md
├── libasm/
│   ├── ft_atoi_base.s
│   ├── ft_list_push_front.s
│   ├── ft_list_remove_if.s
│   ├── ft_list_size.s
│   ├── ft_list_sort.s
│   ├── ft_read.s
│   ├── ft_strcmp.s
│   ├── ft_strcpy.s
│   ├── ft_strdup.s
│   ├── ft_strlen.s
│   └── ft_write.s
├── tester/
│   ├── ft_atoi_base_tester.cpp
│   ├── ft_read_tester.cpp
│   ├── ft_strcmp_tester.cpp
│   ├── ft_strcpy_tester.cpp
│   ├── ft_strdup_tester.cpp
│   ├── ft_strlen_tester.cpp
│   ├── ft_write_tester.cpp
│   ├── main.cpp
│   ├── tester.hpp
│   └── utils.cpp
```

---

## Building

To build the static library and the test program:

```sh
make
```

- This will assemble the functions, create `libasm.a`, and build the C++ test suite (`test_program`).

To build only the library:

```sh
make libasm
```

To build with bonus functions:

```sh
make bonus
```

To clean object files:

```sh
make clean
```

To remove all build artifacts and executables:

```sh
make fclean
```

To rebuild everything:

```sh
make re
```

---

## Testing

A comprehensive C++ test suite is provided in the `tester/` directory. After building, run:

```sh
./test_program
```

This will execute tests for all implemented functions, including edge cases and error handling.

---

## Notes

- All assembly is written for x86-64 Linux using NASM syntax.
- Proper error handling is implemented for system calls (`ft_read`, `ft_write`), including setting the `errno` variable.
- Bonus functions demonstrate basic data structure manipulation in assembly.
- The test suite covers both normal and edge cases for each function.
