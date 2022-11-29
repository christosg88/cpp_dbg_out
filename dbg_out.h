#define ENABLE_DBG_OUT

#ifdef ENABLE_DBG_OUT
#include <iostream>
#include <mutex>

extern std::mutex dbg_out_mtx;

// https://en.cppreference.com/w/cpp/language/variable_template
template <typename ... Args>
void dbg_out_impl(char const * const func,
                  char const * const file,
                  int const &line,
                  Args&& ... args) {
    std::scoped_lock lk(dbg_out_mtx);

    // https://en.cppreference.com/w/cpp/language/fold
    std::cout << func << ' ' << file << ':' << line;
    ((std::cout << ' ' << args), ...) << '\n';
}

// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#define dbg_out(...) dbg_out_impl(__func__, __FILE__, __LINE__, __VA_ARGS__)
#else
#define dbg_out(...)
#endif  // ENABLE_DBG_OUT

