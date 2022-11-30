cmake_minimum_required(VERSION 3.20)
project(cpp_dbg_out)

set(CMAKE_CXX_STANDARD 17)

# enable all warnings and treat them as errors
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wconversion -Wformat=2)
add_compile_options(-Werror)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(-Wcast-align)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # gcc specific warnings
  add_compile_options(-Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wcast-align=strict -Warith-conversion)
endif()

option(ENABLE_STATIC_CHECKS "Enable the cppcheck and clang-tidy static code analyzers" ON)
if (ENABLE_STATIC_CHECKS)
  # enable clang-tidy and cppcheck checks
  find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
  if (CMAKE_CXX_CLANG_TIDY)
    list(APPEND CMAKE_CXX_CLANG_TIDY "--use-color" "--extra-arg=-Wno-unknown-warning-option")
  endif()

  find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
  if (CMAKE_CXX_CPPCHECK)
    list(
      APPEND CMAKE_CXX_CPPCHECK
        "--language=c++"
        "--std=c++17"
        "--enable=all"
        "--suppress=missingIncludeSystem"
        "--template='{file}:{line}:{column}: {severity}: {message} [cppcheck-{id}]\\n{code}'"
    )
  endif()
endif()

set(AVAIL_BUILD_TYPES Debug Release MinSizeRel RelWithDebInfo ASAN MSAN UBSAN TSAN)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${AVAIL_BUILD_TYPES}")

# set the CMAKE_BUILD_TYPE to the default if no build type was specified
set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}'")
  set(
    CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}"
    CACHE
    STRING "Choose the type of build."
    FORCE
  )
endif()

if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST AVAIL_BUILD_TYPES)
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}\nAvailable build types: ${AVAIL_BUILD_TYPES}")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "Debug build" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3" CACHE STRING "Release build" FORCE)
set(CMAKE_CXX_FLAGS_ASAN "-fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O0" CACHE STRING "Address Sanitizer build" FORCE)
set(CMAKE_CXX_FLAGS_MSAN "-fsanitize=memory -fno-omit-frame-pointer -fsanitize-memory-track-origins -g -O0" CACHE STRING "Memory Sanitizer build" FORCE)
set(CMAKE_CXX_FLAGS_UBSAN "-fsanitize=undefined -g -O0" CACHE STRING "Undefined Behaviour Sanitizer" FORCE)
set(CMAKE_CXX_FLAGS_TSAN "-fsanitize=thread -g -O0" CACHE STRING "Thread Sanitizer" FORCE)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(main main.cpp dbg_out.cpp)
target_link_libraries(main Threads::Threads)
target_include_directories(main SYSTEM PRIVATE /usr/local/include/taskflow)

