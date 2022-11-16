// https://godbolt.org/z/WaevozddP
#define ENABLE_DBG_OUT

#ifdef ENABLE_DBG_OUT
#include <iostream>
#include <mutex>

// https://en.cppreference.com/w/cpp/language/variable_template
template <typename ... Args>
void dbg_out_impl(char const * const func,
                  char const * const file,
                  int const &line,
                  Args&& ... args) {
    static std::mutex mtx;
    std::scoped_lock lk(mtx);

    // https://en.cppreference.com/w/cpp/language/fold
    std::cout << func << ' ' << file << ':' << line;
    ((std::cout << ' ' << args), ...) << '\n';
}

// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#define dbg_out(...) dbg_out_impl(__func__, __FILE__, __LINE__, __VA_ARGS__)
#else
#define dbg_out(...)
#endif  // ENABLE_DBG_OUT

constexpr std::string_view am_i_verified() {
  return "I'm using commit verification!";
}

int main() {
    dbg_out("Hello", "World", 3);
    dbg_out("Hello", "World", am_i_verified(), 3);
    return 0;
}

