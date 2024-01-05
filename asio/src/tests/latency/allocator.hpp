//
// allocator.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "asio.hpp"
#include <cstddef>

// Represents a single connection from a client.
class allocator
{
public:
  allocator()
    : in_use_(false)
  {
  }

  void* allocate(std::size_t n)
  {
    if (in_use_ || n > storage_size_)
      return ::operator new(n);
    in_use_ = true;
    return static_cast<void*>(&space_);
  }

  void deallocate(void* p)
  {
    if (p != static_cast<void*>(&space_))
      ::operator delete(p);
    else
      in_use_ = false;
  }

private:
  allocator(const allocator&);
  allocator& operator=(const allocator&);

  // Whether the reusable memory space is currently in use.
  bool in_use_;

  // The reusable memory space made available by the allocator.
  static constexpr std::size_t storage_size_ = 1024;
  asio::aligned_storage_t<storage_size_, alignof(std::max_align_t)> space_;
};

#endif // ALLOCATOR_HPP
