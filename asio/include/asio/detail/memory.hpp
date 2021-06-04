//
// detail/memory.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_MEMORY_HPP
#define ASIO_DETAIL_MEMORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <cstddef>
#include <memory>
#include <new>
#if defined(ASIO_WINDOWS)
# include <malloc.h>
#else
# include <cstdlib>
#endif

#include "asio/detail/throw_exception.hpp"

namespace asio {
namespace detail {

using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

using std::addressof;

} // namespace detail

using std::allocator_arg_t;
# define ASIO_USES_ALLOCATOR(t) \
  namespace std { \
    template <typename Allocator> \
    struct uses_allocator<t, Allocator> : true_type {}; \
  } \
  /**/
# define ASIO_REBIND_ALLOC(alloc, t) \
  typename std::allocator_traits<alloc>::template rebind_alloc<t>
  /**/

inline void* aligned_new(std::size_t align, std::size_t size)
{
#if defined(ASIO_WINDOWS)
  void* ptr = _aligned_malloc(size, align);
  if (!ptr)
  {
    std::bad_alloc ex;
    asio::detail::throw_exception(ex);
  }
  return ptr;
#else
  void *ptr = nullptr;
  if (posix_memalign(&ptr, (align < sizeof(void *) ? sizeof(void *) : align), size))
  {
    std::bad_alloc ex;
    asio::detail::throw_exception(ex);
  }
  return ptr;
#endif
}

inline void aligned_delete(void* ptr)
{
#if defined(ASIO_WINDOWS)
  _aligned_free(ptr);
#else
  std::free(ptr);
#endif
}

} // namespace asio

#endif // ASIO_DETAIL_MEMORY_HPP
