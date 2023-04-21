//
// execution/detail/as_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP
#define ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/detail/memory.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/execution/detail/as_invocable.hpp"
#include "asio/execution/execute.hpp"
#include "asio/execution/set_error.hpp"
#include "asio/traits/start_member.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {
namespace execution {
namespace detail {

template <typename Executor, typename Receiver>
struct as_operation
{
  typename remove_cvref<Executor>::type ex_;
  typename remove_cvref<Receiver>::type receiver_;

  template <typename E, typename R>
  explicit as_operation(ASIO_MOVE_ARG(E) e, ASIO_MOVE_ARG(R) r)
    : ex_(ASIO_MOVE_CAST(E)(e)),
      receiver_(ASIO_MOVE_CAST(R)(r))
  {
  }

  void start() noexcept(true)
  {
#if !defined(ASIO_NO_EXCEPTIONS)
    try
    {
#endif // !defined(ASIO_NO_EXCEPTIONS)
#if defined(ASIO_NO_DEPRECATED)
      ex_.execute(
#else // defined(ASIO_NO_DEPRECATED)
      execution::execute(
          ASIO_MOVE_CAST(typename remove_cvref<Executor>::type)(ex_),
#endif // defined(ASIO_NO_DEPRECATED)
          as_invocable<typename remove_cvref<Receiver>::type,
              Executor>(receiver_
              ));
#if !defined(ASIO_NO_EXCEPTIONS)
    }
    catch (...)
    {
      execution::set_error(
          ASIO_MOVE_OR_LVALUE(
            typename remove_cvref<Receiver>::type)(
              receiver_),
          std::current_exception());
    }
#endif // !defined(ASIO_NO_EXCEPTIONS)
  }
};

} // namespace detail
} // namespace execution
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP
