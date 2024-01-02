//
// executor.cpp
// ~~~~~~~~~~~~
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
#include "asio/execution/executor.hpp"

#include "../unit_test.hpp"

struct not_an_executor
{
};

struct executor
{
  executor()
  {
  }

  executor(const executor&) noexcept
  {
  }

  executor(executor&&) noexcept
  {
  }

  template <typename F>
  void execute(F&& f) const noexcept
  {
    (void)f;
  }

  bool operator==(const executor&) const noexcept
  {
    return true;
  }

  bool operator!=(const executor&) const noexcept
  {
    return false;
  }
};

void is_executor_test()
{
  ASIO_CHECK((
      !asio::execution::is_executor<
        void
      >::value));

  ASIO_CHECK((
      !asio::execution::is_executor<
        not_an_executor
      >::value));

  ASIO_CHECK((
      asio::execution::is_executor<
        executor
      >::value));
}

ASIO_TEST_SUITE
(
  "executor",
  ASIO_TEST_CASE(is_executor_test)
)
