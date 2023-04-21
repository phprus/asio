//
// operation_state.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include "asio/execution/operation_state.hpp"

#include <string>
#include <system_error>
#include "../unit_test.hpp"

#if !defined(ASIO_NO_DEPRECATED)

struct not_an_operation_state_1
{
};

struct not_an_operation_state_2
{
  void start()
  {
  }
};

struct operation_state
{
  void start() noexcept(true)
  {
  }
};

void is_operation_state_test()
{
  ASIO_CHECK((
      !asio::execution::is_operation_state<
        void
      >::value));

  ASIO_CHECK((
      !asio::execution::is_operation_state<
        not_an_operation_state_1
      >::value));

  ASIO_CHECK((
      !asio::execution::is_operation_state<
        not_an_operation_state_2
      >::value));

  ASIO_CHECK((
      asio::execution::is_operation_state<
        operation_state
      >::value));
}

ASIO_TEST_SUITE
(
  "operation_state",
  ASIO_TEST_CASE(is_operation_state_test)
)

#else // !defined(ASIO_NO_DEPRECATED)

ASIO_TEST_SUITE
(
  "operation_state",
  ASIO_TEST_CASE(null_test)
)

#endif // !defined(ASIO_NO_DEPRECATED)
