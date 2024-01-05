//
// high_res_clock.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HIGH_RES_CLOCK_HPP
#define HIGH_RES_CLOCK_HPP

#include <asio.hpp>
#include <cstdint>
#include <chrono>

#if defined(ASIO_WINDOWS)

inline std::uint64_t high_res_clock()
{
  LARGE_INTEGER i;
  QueryPerformanceCounter(&i);
  return i.QuadPart;
}

#elif defined(__GNUC__) && defined(__x86_64__)

inline std::uint64_t high_res_clock()
{
  unsigned long low, high;
  __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
  return (((std::uint64_t)high) << 32) | low;
}

#else

inline std::uint64_t high_res_clock()
{
  auto now = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(
      now.time_since_epoch()).count();
}

#endif

#endif // HIGH_RES_CLOCK_HPP
