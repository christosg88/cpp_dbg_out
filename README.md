## cpp_dbg_out
A `dbg_out` [variadic macro](https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html) that prints the function, file, line and the rest of the arguments from where it's called, to the standard output.

The developer can enable the debug messages by defining `ENABLE_DBG_OUT`, and change the call to a no-op by not defining `ENABLE_DBG_OUT`.

It is thread-safe to call this macro from multiple threads.

It works both in gcc and clang, and requires C++17.

## Compile and run

```bash
cmake -S . -B build
cmake --build build
./build/main
```

So this call inside main(), in the main.cpp file at line 29

```cpp
dbg_out("Hello", "World", 3);
```

Will print:

```
main main.cpp:29 Hello World 3
```

## Disable the `dbg_out`

To disable the printing of the debug messages, just comment out the

```cpp
#define ENABLE_DBG_OUT
```

The definition of `ENABLE_DBG_OUT` can also be done from the terminal, by adding the `-DENABLE_DBG_OUT` compilation option.
