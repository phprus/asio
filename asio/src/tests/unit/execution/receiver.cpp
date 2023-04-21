//
// receiver.cpp
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
#include "asio/execution/receiver.hpp"

#include <string>
#include <system_error>
#include "../unit_test.hpp"

#if !defined(ASIO_NO_DEPRECATED)

struct not_a_receiver
{
};

struct receiver
{
  receiver()
  {
  }

  receiver(const receiver&)
  {
  }

  receiver(receiver&&)
  {
  }

  template <typename E>
  void set_error(ASIO_MOVE_ARG(E) e) noexcept(true)
  {
    (void)e;
  }

  void set_done() noexcept(true)
  {
  }
};

struct receiver_of_0
{
  receiver_of_0()
  {
  }

  receiver_of_0(const receiver_of_0&)
  {
  }

  receiver_of_0(receiver_of_0&&)
  {
  }

  template <typename E>
  void set_error(ASIO_MOVE_ARG(E) e) noexcept(true)
  {
    (void)e;
  }

  void set_done() noexcept(true)
  {
  }

  void set_value()
  {
  }
};

struct receiver_of_1
{
  receiver_of_1()
  {
  }

  receiver_of_1(const receiver_of_1&)
  {
  }

  receiver_of_1(receiver_of_1&&)
  {
  }

  template <typename E>
  void set_error(ASIO_MOVE_ARG(E) e) noexcept(true)
  {
    (void)e;
  }

  void set_done() noexcept(true)
  {
  }

  void set_value(int) noexcept(true)
  {
  }
};

struct receiver_of_2
{
  receiver_of_2()
  {
  }

  receiver_of_2(const receiver_of_2&)
  {
  }

  receiver_of_2(receiver_of_2&&)
  {
  }

  template <typename E>
  void set_error(ASIO_MOVE_ARG(E) e) noexcept(true)
  {
    (void)e;
  }

  void set_done() noexcept(true)
  {
  }

  void set_value(int, std::string)
  {
  }
};

void is_receiver_test()
{
  ASIO_CHECK((
      !asio::execution::is_receiver<
        void,
        std::error_code
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver<
        not_a_receiver,
        std::error_code
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver<
        receiver,
        std::error_code
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver<
        receiver_of_0,
        std::error_code
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver<
        receiver_of_1,
        std::error_code
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver<
        receiver_of_2,
        std::error_code
      >::value));
}

void is_receiver_of_test()
{
  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        void
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        void,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        not_a_receiver
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        not_a_receiver,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        not_a_receiver,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver_of<
        receiver_of_0
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_0,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_0,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_1
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver_of<
        receiver_of_1,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_1,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_2
      >::value));

  ASIO_CHECK((
      !asio::execution::is_receiver_of<
        receiver_of_2,
        int
      >::value));

  ASIO_CHECK((
      asio::execution::is_receiver_of<
        receiver_of_2,
        int,
        std::string
      >::value));
}

void is_nothrow_receiver_of_test()
{
  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        void
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        void,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        not_a_receiver
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        not_a_receiver,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        not_a_receiver,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_0
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_0,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_0,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_1
      >::value));

  ASIO_CHECK((
      asio::execution::is_nothrow_receiver_of<
        receiver_of_1,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_1,
        int,
        std::string
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_2
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_2,
        int
      >::value));

  ASIO_CHECK((
      !asio::execution::is_nothrow_receiver_of<
        receiver_of_2,
        int,
        std::string
      >::value));
}

ASIO_TEST_SUITE
(
  "receiver",
  ASIO_TEST_CASE(is_receiver_test)
  ASIO_TEST_CASE(is_receiver_of_test)
  ASIO_TEST_CASE(is_nothrow_receiver_of_test)
)

#else // !defined(ASIO_NO_DEPRECATED)

ASIO_TEST_SUITE
(
  "receiver",
  ASIO_TEST_CASE(null_test)
)

#endif // !defined(ASIO_NO_DEPRECATED)
