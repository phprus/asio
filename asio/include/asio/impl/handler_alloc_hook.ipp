//
// impl/handler_alloc_hook.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IMPL_HANDLER_ALLOC_HOOK_IPP
#define ASIO_IMPL_HANDLER_ALLOC_HOOK_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/memory.hpp"
#include "asio/detail/thread_context.hpp"
#include "asio/detail/thread_info_base.hpp"
#include "asio/handler_alloc_hook.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size, ...)
{
  (void)size;
  return asio_handler_allocate_is_no_longer_used();
}

asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size, ...)
{
  (void)pointer;
  (void)size;
  return asio_handler_deallocate_is_no_longer_used();
}

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IMPL_HANDLER_ALLOC_HOOK_IPP
